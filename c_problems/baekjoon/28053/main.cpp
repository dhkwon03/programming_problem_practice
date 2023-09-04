#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

/*
i) a, b are not coprime
a = d*(alpha), b = d * (beta), gcd(a,b) = d
a+bk = d((alpha)+b*(beta))
a+b(k+p) = d((alpha)+(beta)*(k+p)) .... p is arbitrary integer which is larger than 1
Thus, all combinations in the sequence are not coprime.

ii) a, b are coprime
prove that a+bk, a+b(k+1) are coprime.
pf) assume gcd(a+bk, a+b(k+1)) = d (d > 1)
(1) : a+bk = d*(alpha)
(2) : a+b(k+1) = d * (beta)
Then, alpha and beta are coprime.

(2) - (1) : b = d(beta - alpha) --> b is multiple of d
(1) + (2) : 2a + b(2k+1) = d(alpha + beta)
b(2k+1) is multiple of d, d(alpha + beta) is also multiple of d --> 2a is multiple of d --> a is multiple of d
This violates the assumption that a, b are coprime. (contradiction)
Thus, a+bk, a+b(k+1) are coprime.

Q.E.D.

-------Conclusion-------
To make such sequence of operations exist, a and b should be coprime.
Also, we could apply operations (i.e. remove two coprime integers in the sequence) as removing two neighbor numbers in the sequence. (if a and b are coprime)
*/

int gcd(int a, int b)
{
	int temp;
	int va, vb;

	va = a;
	vb = b;

	if(va < vb) {
		temp = va;
		va = vb;
		vb = temp;
	}
	else if(va == vb) {
		return va;
	}

	long long int ca, cb;
	long long int q, r;

	ca = va;
	cb = vb;
	while(1) {
		q = ca / cb;
		r = ca % cb;

		if(r == 0) break;
		else {
			ca = cb;
			cb = r;
		}
	}

	return cb;
}

int main()
{
	long long int N, A, B;

	std::cin >> N >> A >> B;	

#ifdef DEBUG
	printf("gcd(A, B) = %d\n", gcd(A, B));
#endif

	if(gcd(A, B) != 1) printf("No\n");
	else {
		printf("Yes\n");

		for(int i = 0; i < (2*N); i += 2) {
			long long int ans1, ans2;

			ans1 = A + (i * B);
			ans2 = A + ((i + 1) * B);

			printf("%lld %lld\n", ans1, ans2);
		}
	}

	return 0;
}
