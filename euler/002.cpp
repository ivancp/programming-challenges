#include <iostream>

using namespace std;


int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        unsigned long long n;
        cin >> n;

	unsigned long long a = 1,b = 2,curr = 0,sum = 2;
	while(curr <= n){
		curr = a + b;
		a = b;
		b = curr;
		if(curr % 2 == 0 && curr<= n){
			sum += curr;
		}
	}

	cout<<sum<<endl;


    }
    return 0;
}
