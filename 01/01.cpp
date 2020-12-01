#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int process(int *numbers, int length){
	int toFind = 0;
	int found = 0;
	int running = 1;

	for(int i=0; running && i<length;i++){
		toFind = 2020-numbers[i];
		for(int j=0; j<length;j++){
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
	string inputLine;
	ifstream inputFile ("./input.txt");
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

		/*for(int i=0; i<lineCount;i++){
			cout << numbers[i] << '\n';
		}*/

		int result = process(numbers,lineCount);

		delete numbers;

		if(result){
			cout << "result: " << result << "\n";
		}else{
			return 1;
		}


	}else{
		return 1;
	}

	return 0;
}