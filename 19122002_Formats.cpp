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

float FloatingFunc(string passed_string, int T, int E){
	
	char signBit = passed_string[0];														//storing sign bit as char
	string mantBitStr = passed_string.substr(1,E);											//storing integerbitsin string format
	string fracBitStr = passed_string.substr(E+1);											//storing fraction bits in strng format

	int sign = 1;																			//determining and storing sign bit
	if ( signBit == '1')
		sign = -1;

	int loopVar1 = mantBitStr.size() - 1;													//initializing first loop variable
	int Mantissa = 0;																		//variable for final integer part of number
	int degree = 1;
	while(loopVar1 >= 0){																	//first loop for cycling through the integer part bit string
		int temp = 0;																		//temporary integer storage
		if (mantBitStr[loopVar1] == '1')
			temp = 1;
		Mantissa = Mantissa + (degree * temp);												//final integer part key manipulation
		degree = degree * 2;
		loopVar1--;																			//decrementing first loop variable
	}

	int loopVar2 = 0;																		//initializing second loop variable
	float fraction = 0.0d;																	//float variable for storing final fractional part
	float frac_degree = 0.5;
	while(loopVar2 <= (fracBitStr.size()-1)){												//second loop to cycle through the fractional part bits in *descending* order
		int temp = 0;																		//re-initialized temporary integer storage
		if(fracBitStr[loopVar2] == '1')
			temp = 1;
		fraction = fraction + (frac_degree * temp);											//final fractional part key manipulation
		frac_degree = frac_degree/2;
		loopVar2++; 																		//incrementing second loop variable as descending scheme applied
	}
	float fin = Mantissa + fraction;														//addition of obtained results of integer and fractional part

	return (sign * fin);																	//return final number
}																							//Working FxP conversion function



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
		if (binary_String.size() != T)
			return
		/*code for single*/
	}
	else if(selection_route == "All"){														//If asked for the All option
		/*code for all*/
	}
 return 0;
}

