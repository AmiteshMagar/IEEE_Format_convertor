#include<bits/stdc++.h>
#include<sstream>
#include<string>

using namespace std;

int IntegerFunc(string passed_string){

	char signBit = passed_string[0];														//storing sign bit as char
	string mantBitStr = passed_string.substr(1);											//storing Mantissa bits

	int sign = 1;																			//determining and storing sign bit
	if ( signBit == '1')
		sign = -1;

	int loopVar = mantBitStr.size() -1;														//initializing loop variable
	int final_number = 0;																	//variable for final number
	int degree = 1;
	while(loopVar >= 0){																	//loop for cycling through the mantissa bit string
		int temp = 0;																		//temporary integer storage
		if (mantBitStr[i] == '1')
			temp = 1;
		final_number = final_number + (degree * temp);										//final number key manipulation
		degree = degree * 2;
		loopVar--;																			//decrementing loop variable
	}
	return  (sign * final_number);															//return final number 
}																							//Working Integer conversion function	

int main(int argc, char* argv[]){															//driver code
	
	stringstream Total(argv[1]);															//String stream for Total (T) parameter passed
	int T = 0;
	Total >> T;																				//Variable that stores the Total (T) parameter passed
	
	stringstream Expo(argv[2]);																//String stream variable for Exponent (E) parameter passed
	int E = 0;
	Expo >> E;																				//Variable to store the Exponent (E) parameter passed

	string selection_route = argv[3];														//Variable for the third parameter passed

	if(selection_route == "Single"){														//If asked the Single option 

		string binary_String = argv[4];														//The variable for storing the binary string
		/*code for single*/
	}
	else if(selection_route == "All"){														//If asked for the All option
		/*code for all*/
	}

}

