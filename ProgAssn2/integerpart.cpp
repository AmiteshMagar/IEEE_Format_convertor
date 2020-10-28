#include<bits/stdc++.h>
#include<sstream>
#include<string>

using namespace std;

int IntegerFunc(string passed_string){

	char signBit = passed_string[0];
	string mantBitStr = passed_string.substr(1);

	int sign = 1;
	if ( signBit == '1')
		sign = -1;

	int i = mantBitStr.size() -1;
	int fin = 0;
	int count = 1;
	while(i >= 0){
		int temp = 0;
		if (mantBitStr[i] == '1')
			temp = 1;
		fin = fin + (count * temp);
		count = count * 2;
		i--;
	}

	return  (sign * fin);
}


int main(){
	cout << IntegerFunc("1001011") << endl;
	return 0;
}