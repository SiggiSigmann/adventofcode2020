#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <bitset>

using namespace std;

/*##############################################################################
# enum for different operations
##############################################################################*/
enum Ops{
	acc, 
	jmp,
	nop
};

/*##############################################################################
# store oparation and parameter
##############################################################################*/
struct Operation{
	int amount;
	Ops op;
};

/*##############################################################################
# counts number of lines in given file
##############################################################################*/
int numberOfLines(string fileName){
	int ruleCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine))ruleCount++;

		cout << "Number of Rules: " << ruleCount << '\n';

		inputFile.close();	
	}

	return ruleCount;
}

/*##############################################################################
# loads each line in operations array
##############################################################################*/
int loadFileInArray(string fileName, Operation *ops){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert line into operation
		for(int i=0; getline(inputFile, inputLine);i++){
			//find operation
			spacer = inputLine.find(" ");
			string operation = inputLine.substr(0, spacer);
			if(operation == "acc"){
				ops[i].op = acc;
			}else if (operation == "jmp"){
				ops[i].op = jmp;
			}else{
				ops[i].op = nop;
			}
			
			//find parameter
			ops[i].amount = stoi(inputLine.substr(spacer+1, inputLine.length()-(spacer+1)));
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# find Loop in input code and switch jmp and nop at <toSwitch>
##############################################################################*/
int findeLoop(Operation *ops, int opNumbers, int *broken, int toSwitch){
//parameter for processor
	int accumulator = 0;
	int operationPointer = 0;

	//store which operation are already processed
	long long int *alreadyDone = new long long int[(opNumbers/64)+1];
	for(int i = 0; i<((opNumbers/64)+1); i++){
		alreadyDone[i] = 0;
	}

	//execute code
	while(1){
		//check operationPointer
		if(opNumbers<=operationPointer || opNumbers<0) break;
		
		//check if loop exists
		int idx_array = operationPointer/64;
		long int idx = operationPointer%64;

		if(alreadyDone[idx_array] & (long long int)pow(2,idx)){
			*broken =0;
			break;
		}

		//store execution
		alreadyDone[idx_array] |= (long long int)(pow(2,idx));

		Operation op = ops[operationPointer];

		//switch jmp and nop
		if(operationPointer == toSwitch){
			if(op.op == jmp){
				op.op = nop;
			}else if(op.op == nop){
				op.op = jmp;
			}else{
				*broken =0;
				break;
			}
		}

		//eceute
		switch(op.op){
			case acc:
				accumulator += op.amount;
				operationPointer++;
				break;

			case jmp:
				operationPointer += op.amount;
				break;

			case nop:
				operationPointer++;
				break;
		}

		//check if end ob code reached
		if(opNumbers==(operationPointer-1)){
			break;
		}
	}

	delete alreadyDone;

	return accumulator;
}

int findFix(Operation *ops, int opNumbers){
	int res = 0;
	int broken;

	//try to change each line and try if loop still exists
	for(int i = 0; i<opNumbers; i++){
		broken = 1;
		res = findeLoop(ops, opNumbers, &broken, i);
		if(broken) return res;

	}

	return 0;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int opNumbers = numberOfLines(filename);
	if(!opNumbers) return 1;

	//get file as an array
	Operation *ops = new Operation[opNumbers];
	int res = loadFileInArray(filename, ops);
	if(!res) return 1;

	//execute bruteforce fix
	res = findFix(ops, opNumbers);
	cout << "fixed value: " << res << "\n";

	delete ops; 

	return 0;
}