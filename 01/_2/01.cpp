#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*##############################################################################
# calculates solution recursively
# offset is an array containing the current offset in the numbers array, n contains 
# the length of the offset array and i contains 
# the current recurrent step
# Returns finisflag 1= finished
##############################################################################*/
int proccesNth(int *numbers, int length, int *offsets, int n, int i){
	int done = 0;
	int start = 0;

	//calculate startvalue 
	if(i>0){
		start = offsets[i-1]+1;
	}
	
	for(offsets[i] = start; !done && (offsets[i])<length; (offsets[i])++){
		//ceck if last recurence step
		if((i+1) == n){
			int sum = 0;
			
			//calculate sum of all chosen numbers
			for(int j =0; j<n; j++){
				sum += numbers[offsets[j]];
			}

			if(sum == 2020){
				cout << "i:" << i << " |" << offsets[0] << " " << offsets[1] <<"\n";
				return 1;
			}
			
		}else{
			//next step
			done = proccesNth(numbers, length, offsets, n, i+1);
			if(done){
				//break recurent
				return 1;
			}
		}
	}
	return 0;
}

/*##############################################################################
# Proccess numbers array by adding n elements together until the sum ist 2020.
# Returns the product of those n numbers.
##############################################################################*/
int process(int *numbers, int length, int n){
	//create offset array which will holds the offsets of the numbers in the 
	//numbers array
	int *offsets = new int[n];
	for(int i=0;i<n;i++){
		offsets[i] = 0;
	}

	//calculate solution
	int erg = proccesNth(numbers, length, offsets, n, 0);
	int result = 1 ;

	//multiply all numbers together if a solution was found.
	if(erg){
		for(int i=0;i<n;i++){
			result *= numbers[offsets[i]];
		}
		delete offsets;
		return result;
	}

	return 0;
}

int main(int argc, char *argv[]){
	if(argc == 1){
		cout << "missing argument" << "\n";
		return 1;
	}

	string inputLine;
	ifstream inputFile ("../input.txt");
	if (inputFile.is_open()){
		int lineCount = 0;
		while (getline(inputFile, inputLine)) lineCount++;

		cout << "Number of Lines: " << lineCount << '\n';

		inputFile.clear();
		inputFile.seekg(0);

		int *numbers = new int[lineCount];

		for(int i=0; getline(inputFile, inputLine);i++){
			numbers[i]= stoi(inputLine);
		}
		inputFile.close();

		int countOfNumbers = stoi(argv[1]);

		int result = process(numbers,lineCount,countOfNumbers);

		delete numbers;

		if(result){
			cout << "result: " << result << "\n";
		}else{
			cout << "no solution found \n";
		}

	}else{
		return 1;
	}

	return 0;
}