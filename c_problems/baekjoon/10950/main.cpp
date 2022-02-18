#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
    int t;
    
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        int input1, input2;
        
        cin >> input1 >> input2;
        
        cout << (input1 + input2) << endl;
    }
    
    return 0;
}
