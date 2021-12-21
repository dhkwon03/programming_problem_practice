% Common Spatial Pattern 알고리즘을 Matlab으로
% 구현한 소스코드 입니다.
% 데이터는 이용하지 않고,
% 랜덤으로 데이터를 생성해서 수행해보도록 하겠습니다.
function CSP()
channel = 100;
sampling=200;
trials = 100;
class_1 = normrnd(0,1,[sampling,channel,trials]); % 200개의 샘플링 개수 * 채널의 개수 * trial의 개수 신호(Class 1)
class_2 = normrnd(2,1,[sampling,channel,trials]); % 200개의 샘플링 개수 * 채널의 개수 * trial의 개수 신호(Class 2)
 
%먼저 normalized covariance matrix를 구합니다.
for i=1:trials
    C1_covariance(:,:,i) = (class_1(:,:,i)' * class_1(:,:,i)) / trace(class_1(:,:,i)' * class_1(:,:,i)); % (X*X') / tr(X*X')
    C2_covariance(:,:,i) = (class_2(:,:,i)' * class_2(:,:,i)) / trace(class_2(:,:,i)' * class_2(:,:,i));
end
 
% 평균 공분산 행렬을 구할겁니다..
% 아주 간단하게..
mean_C1_cov=mean(C1_covariance, 3);
mean_C2_cov=mean(C2_covariance, 3);
 
%평균 공분산 행렬을 더해주고..
C_sum=mean_C1_cov + mean_C2_cov;
 
%고유값 분해..
[EVecsum,EValsum]= eig(C_sum);
[EValsum, ind] = sort(diag(EValsum), 'descend');
EVecsum = EVecsum(:, ind);
Q = zeros(channel , channel);
Q = sqrt(pinv(diag(EValsum))) *  EVecsum'; %백색화변환행렬 만들기 끝
 
% 우리는 백색화변환된 행렬을만들거에요 ~
S1=Q * mean_C1_cov * Q';
S2=Q * mean_C2_cov * Q';
 
% 이걸 다시 분해합니다 ~
[B, D] = eig(S1, S2);
[D,ind]=sort(diag(D));
B=B(:,ind);
CSP_filter= zeros(channel , channel);
 
%csp필터를 계산합니다.
CSP_filter =  B' * Q;
 
%상위 m 개 하위 m개를 선택해봅니다..
m=2;
sel_CSP_filter(1:m,:) = CSP_filter(1:m,:);
sel_CSP_filter(m+1:2*m,:) = CSP_filter(channel-(m-1):channel,:);
 
%필터링된신호를 이용해서 특징(분산) 계산하기.
for i = 1: trials %실험이 100개니까 100 번돌려~
    trans_signal_C1(:,:,i) = sel_CSP_filter * class_1(:,:,i)';
    trans_signal_C2(:,:,i) = sel_CSP_filter * class_2(:,:,i)';
    
    var_signal1(:,:,i) = var(trans_signal_C1(:,:,i)');
    var_signal2(:,:,i) = var(trans_signal_C2(:,:,i)');
    FEATURE_C1(i, :) = log10(var_signal1(:,:,i)/sum(var_signal1(:,:,i)));
    FEATURE_C2(i, :) = log10(var_signal2(:,:,i)/sum(var_signal2(:,:,i))); %특징 계산
end
 
% 원래 신호의 분산값을 그려보기위해..
for i = 1: trials %실험이 100개니까 100 번돌려~
    var_signal11(:,:,i) = var(class_1(:,:,i)');
    var_signal22(:,:,i) = var(class_2(:,:,i)');
    FEATURE_C11(i, :) = log10(var_signal11(:,:,i)/sum(var_signal11(:,:,i)));
    FEATURE_C22(i, :) = log10(var_signal22(:,:,i)/sum(var_signal22(:,:,i))); %특징 계산
end
%%
end