#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*##############################################################################
# Proccess numbers array by adding two elements together until the sum ist 2020.
# Returns the product of those two numbers.
##############################################################################*/
int process(int *numbers, int length){
	//holds the two elements
	int toFind = 0;
	int found = 0;

	//running flag
	int running = 1;

	//try all combination of two elements from the array
	for(int i=0; running && i<length;i++){
		toFind = 2020-numbers[i];
		for(int j=i+1; j<(length-1);j++){
			if(toFind == numbers[j]){
				found = numbers[j];
				running = 0;
				break;
			}
		}
	}
	cout << (2020-toFind) << " " <<found<< "\n";
	return (2020-toFind)  * found;
}

int main(){
	//load array from file 
	string inputLine;
	ifstream inputFile ("../input.txt");
	if (inputFile.is_open()){

		//get line number
		int lineCount = 0;
		while (getline(inputFile, inputLine)) lineCount++;
		cout << "Number of Lines: " << lineCount << '\n';

		inputFile.clear();
		inputFile.seekg(0);

		//load array from file
		int *numbers = new int[lineCount];
		for(int i=0; getline(inputFile, inputLine);i++){
			numbers[i]= stoi(inputLine);
		}
		inputFile.close();

		//clac results
		int result = process(numbers,lineCount);

		delete numbers;

		//check result
		if(!result){
			return 1;
		}

		cout << "result: " << result << "\n";

	}else{
		return 1;
	}

	return 0;
}