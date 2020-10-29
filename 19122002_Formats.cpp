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
	char signBit = passed_string[0];
	string expoBitStr = passed_string.substr(1,E);
	string mantBitStr = passed_string.substr(E+1);

	stringstream parser;
	string parsed;

	int sign = 1;
	if ( signBit == '1')
		sign = -1;

	int loopVar1 = expoBitStr.size() - 1;
	int Exponent = 0;
	int exp_degree = 1;
	while( loopVar1 >= 0){
		int temp = 0;
		if (expoBitStr[loopVar1] == '1')
			temp = 1;
		Exponent = Exponent + (exp_degree * temp);
		exp_degree = exp_degree * 2;
		loopVar1--;
	}

	int loopVar2 = 0;
	float Mantissa = 0.0;
	float mant_degree = 0.5;
	while(loopVar2 <= (mantBitStr.size() - 1)){
		int temp = 0;
		if(mantBitStr[loopVar2] == '1')
			temp = 1;
		Mantissa = Mantissa + (mant_degree * temp);
		mant_degree = mant_degree/2;
		loopVar2++;
	}
	if(Exponent == 0 && Mantissa == 0){
		return "0";
	}
	else if(Exponent == 0 && Mantissa !=0){
		Exponent = Exponent - (pow(2 , E-1) - 2);
		Mantissa = Mantissa * sign * pow(2,Exponent);
		parser << Mantissa;
		parser >> parsed;
		string DeNorm = "    Denormal number ";
		parsed = DeNorm.append(parsed);
		return parsed;
	}
	else if(Exponent == (pow(2,E) -1)){
		if(Mantissa == 0.0 && sign == 1){
			return "+infinity";
		}
		else if(Mantissa == 0.0 && sign == -1){
			return "-infinity";
		}
		else{
			return "NAN";
		}
	}
	else if(Exponent != 0 && Exponent != (pow(2,E) -1)){
		Exponent = Exponent - (pow(2, E-1) - 1);
		Mantissa = (1.0 + Mantissa) * sign * pow(2,Exponent);
		parser << Mantissa;
		parser >> parsed;
		return parsed;
	}

}

int main(int argc, char* argv[]){												//driver code

	stringstream Total(argv[1]);												//String stream for Total (T) parameter passed
	int T = 0;
	Total >> T;																	//Variable that stores the Total (T) parameter passed

	stringstream Expo(argv[2]);													//String stream variable for Exponent (E) parameter passed
	int E = 0;
	Expo >> E;																	//Variable to store the Exponent (E) parameter passed

	string selection_route = argv[3];

	ofstream Output_File;
	string FileName = "19122002_";
	FileName.append(to_string(T));
	FileName.append("_");
	FileName.append(to_string(E));
	FileName.append("_");

	if(selection_route == "Single"){											//If asked the Single option

		string binary_String = argv[4];											//The variable for storing the binary string
		if (binary_String.size() != T)
			return 0;

		FileName.append("Single_");
		FileName.append(binary_String);
		FileName.append(".txt");

		Output_File.open(FileName, ios::out| ios::trunc);
		Output_File<<"combinations"<<setw(20)<<"integer"<<setw(20)\
		<<"fixed point"<<setw(20)<<"FP\n";

		Output_File << binary_String <<setw(20)\
		<< IntegerFunc(binary_String) << setw(20)\
		<< FloatingFunc(binary_String, T, E) << setw(20)\
		<< FloatingPointFunc(binary_String, T, E)<<endl;
	}
	else if(selection_route == "All"){											//If asked for the All option

		FileName.append("All.txt");
		Output_File.open(FileName, ios::out | ios::trunc);
		Output_File<<"combinations"<<setw(20)<<"integer"<<setw(20)\
		<<"fixed point"<<setw(20)<<"FP\n";

		string servantString(T, '0');
		string masterString = "1";
		masterString = masterString.append(servantString);
		bitset<32> bset1(masterString);
		bitset<32> bset2(0);
		while(bset2 != bset1){

			string binary_String = bset2.to_string().substr(32-T);

			Output_File << binary_String <<setw(20)\
			<< IntegerFunc(binary_String) << setw(20)\
			<< FloatingFunc(binary_String, T, E) << setw(20)\
			<< FloatingPointFunc(binary_String, T, E);

			bset2 = bitset<32>(bset2.to_ulong() + 1ULL);
			if(bset2 != bset1)
				Output_File << endl;
		}
	}
	Output_File.close();
	cout << "Done!"<<endl;
	return 0;
}
