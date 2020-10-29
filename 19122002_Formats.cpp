#include<bits/stdc++.h>
#include<sstream>
#include<string>
#include<fstream>

using namespace std;

int IntegerFunc(string passed_string){

	char signBit = passed_string[0];											//storing sign bit as char
	string mantBitStr = passed_string.substr(1);								//storing Mantissa bits

	int sign = 1;																//determining and storing sign bit
	if ( signBit == '1')
		sign = -1;

	int loopVar = mantBitStr.size() -1;											//initializing loop variable
	int final_number = 0;														//variable for final number
	int degree = 1;
	while(loopVar >= 0){														//loop for cycling through the mantissa bit string
		int temp = 0;															//temporary integer storage
		if (mantBitStr[loopVar] == '1')
			temp = 1;
		final_number = final_number + (degree * temp);							//final number key manipulation
		degree = degree * 2;
		loopVar--;																//decrementing loop variable
	}
	return  (sign * final_number);												//return final number
}																				//Working Integer conversion function

float FloatingFunc(string passed_string, int T, int E){

	char signBit = passed_string[0];											//storing sign bit as char
	string mantBitStr = passed_string.substr(1,E);								//storing integerbitsin string format
	string fracBitStr = passed_string.substr(E+1);								//storing fraction bits in strng format

	int sign = 1;																//determining and storing sign bit
	if ( signBit == '1')
		sign = -1;

	int loopVar1 = mantBitStr.size() - 1;										//initializing first loop variable
	int Mantissa = 0;															//variable for final integer part of number
	int degree = 1;
	while(loopVar1 >= 0){														//first loop for cycling through the integer part bit string
		int temp = 0;															//temporary integer storage
		if (mantBitStr[loopVar1] == '1')
			temp = 1;
		Mantissa = Mantissa + (degree * temp);									//final integer part key manipulation
		degree = degree * 2;
		loopVar1--;																//decrementing first loop variable
	}

	int loopVar2 = 0;															//initializing second loop variable
	float fraction = 0.0d;														//float variable for storing final fractional part
	float frac_degree = 0.5;
	while(loopVar2 <= (fracBitStr.size()-1)){									//second loop to cycle through the fractional part bits in *descending* order
		int temp = 0;															//re-initialized temporary integer storage
		if(fracBitStr[loopVar2] == '1')
			temp = 1;
		fraction = fraction + (frac_degree * temp);								//final fractional part key manipulation
		frac_degree = frac_degree/2;
		loopVar2++; 															//incrementing second loop variable as descending scheme applied
	}
	float fin = Mantissa + fraction;											//addition of obtained results of integer and fractional part

	if(Mantissa == 0 && fraction == 0)
		return 0;
	return (sign * fin);														//return final number
}																				//Working FxP conversion function

string FloatingPointFunc(string passed_string, int T, int E){

	char signBit = passed_string[0];											//storing sign bit as char
	string expoBitStr = passed_string.substr(1,E);								//storing Exponent bits
	string mantBitStr = passed_string.substr(E+1);								//storng Mantissa bits

	stringstream parser;														//string stream for final output
	string parsed;																//string variable for storing string

	int sign = 1;
	if ( signBit == '1')														//determining and storing sign bit
		sign = -1;

	int loopVar1 = expoBitStr.size() - 1;										//initializing first loop variable
	int Exponent = 0;															//variable for final exponent variable
	int exp_degree = 1;
	while( loopVar1 >= 0){														//first loop to cycle through exponent bits
		int temp = 0;															//temporary integer storage
		if (expoBitStr[loopVar1] == '1')
			temp = 1;
		Exponent = Exponent + (exp_degree * temp);								//final exponent key manipulation
		exp_degree = exp_degree * 2;
		loopVar1--;																//decrementing first loop Variable
	}

	int loopVar2 = 0;															//initializing second loop Variable
	float Mantissa = 0.0;														//float variable for storing Mantissa < 1
	float mant_degree = 0.5;
	while(loopVar2 <= (mantBitStr.size() - 1)){									//second loop to cycle through Mantissa bits in reverse order
		int temp = 0;															//re-initialized temporary Variable
		if(mantBitStr[loopVar2] == '1')
			temp = 1;
		Mantissa = Mantissa + (mant_degree * temp);								//final float variable key manipulation
		mant_degree = mant_degree/2;
		loopVar2++;																//incrementing the second loop variable as proceeded in reverse order
	}
	if(Exponent == 0 && Mantissa == 0){											//Case for number being zero, required to omit the +0, -0 argument
		return "0";
	}
	else if(Exponent == 0 && Mantissa !=0){										//block for Denormal number checking and execution
		Exponent = Exponent - (pow(2 , E-1) - 2);								//removing bias and normalizing exponent variable
		Mantissa = Mantissa * sign * pow(2,Exponent);							//key manipulationfor output

		parser << Mantissa;														//passing final mantissa to sstream for parsing
		parser >> parsed;														//demanding the parsed value in string format
		string DeNorm = "    Denormal number ";									//extra append to indicate "Denormal numbers", added extra spaces to match the output file
		parsed = DeNorm.append(parsed);

		return parsed;															//returning the final variable
	}
	else if(Exponent == (pow(2,E) -1)){											//block for NAN, +infinity and -infinity sieve
		if(Mantissa == 0.0 && sign == 1){										//+infinity Case
			return "+infinity";
		}
		else if(Mantissa == 0.0 && sign == -1){									//-infinity Case
			return "-infinity";
		}
		else{																	//NAN Case
			return "NAN";
		}
	}
	else if(Exponent != 0 && Exponent != (pow(2,E) -1)){						//Block for normal numbers, direct execution as exceptions have been already dealt with
		Exponent = Exponent - (pow(2, E-1) - 1);								//remove bias from the exponent variable
		Mantissa = (1.0 + Mantissa) * sign * pow(2,Exponent);					//key manipulation of final Variable

		parser << Mantissa;														//passing final value to sstream for parsing
		parser >> parsed;														//demanding the parsed value in string format

		return parsed;															//returning the final value
	}
}																				//Working FP conversion function

int main(int argc, char* argv[]){												//driver code

	stringstream Total(argv[1]);												//String stream for Total (T) parameter passed
	int T = 0;
	Total >> T;																	//Variable that stores the Total (T) parameter passed

	stringstream Expo(argv[2]);													//String stream variable for Exponent (E) parameter passed
	int E = 0;
	Expo >> E;																	//Variable to store the Exponent (E) parameter passed

	string selection_route = argv[3];

	ofstream Output_File;														//initializing file stream for output storage
	string FileName = "19122002_";
	FileName.append(to_string(T));
	FileName.append("_");
	FileName.append(to_string(E));
	FileName.append("_");														//multiple appends to match the requests of question

	if(selection_route == "Single"){											//Block for 'Single' operation

		string binary_String = argv[4];											//variable for storing binary string
		if (binary_String.size() != T)											//primary condition before execution to check if right input parameters were provided
			return 0;															//termination if defaulted

		FileName.append("Single_");
		FileName.append(binary_String);
		FileName.append(".txt");												//special appends to file name for 'Single' operation

		Output_File.open(FileName, ios::out| ios::trunc);						//opening the file for storage, file name has been adjusted

		Output_File<<"combinations"<<setw(20)<<"integer"<<setw(20)\
		<<"fixed point"<<setw(20)<<"FP\n";										//First line to show columns

		Output_File << binary_String <<setw(20)\
		<< IntegerFunc(binary_String) << setw(20)\
		<< FloatingFunc(binary_String, T, E) << setw(20)\
		<< FloatingPointFunc(binary_String, T, E) ;								//adding line to output file, lagging end line command removed
	}

	else if(selection_route == "All"){											//Block for 'All' operation

		FileName.append("All.txt");												//special appends to filename for 'All' operation
		Output_File.open(FileName, ios::out | ios::trunc);
		Output_File<<"combinations"<<setw(20)<<"integer"<<setw(20)\
		<<"fixed point"<<setw(20)<<"FP\n";

		string servantString(T, '0');											//full zero string generated
		string masterString = "1";												//maximum limit + 1 bit string, acts as the boundary condition
		masterString = masterString.append(servantString);

		bitset<32> bset1(masterString);											//initializing first bitset variable that acts as test condition to keep second variable in check
		bitset<32> bset2(0);													//initializing second bitset variable, starting from all-Zero and incremented later

		while(bset2 != bset1){													//conditionfor loop to run,

			string binary_String = bset2.to_string().substr(32-T);				//getting binary string from the cycling bitset variable used in loop

			Output_File << binary_String <<setw(20)\
			<< IntegerFunc(binary_String) << setw(20)\
			<< FloatingFunc(binary_String, T, E) << setw(20)\
			<< FloatingPointFunc(binary_String, T, E);							//adding line to output file

			bset2 = bitset<32>(bset2.to_ulong() + 1ULL);						//increment of the bitset for loop cycling
			if(bset2 != bset1)													//special condition introduced to avoid lagging end line command
				Output_File << endl;
		}
	}
	Output_File.close();														//closing output file
	cout << "Done!"<<endl;														//Terminal message to show successful execution
	return 0;																	//final return, End of program
}
