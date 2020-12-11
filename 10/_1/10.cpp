#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

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
int loadFileInArray(string fileName, int *numbers){
	string inputLine;
	ifstream inputFile (fileName);

	//add charger
	numbers[0] = 0;

	if (inputFile.is_open()){
		//convert line into long long int
		for(int i=1; getline(inputFile, inputLine);i++){
			numbers[i] = stoll(inputLine);
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

void sortNumbers(int *numbers, int length){
	for(int i = 0; i<length-1 ; i++){
		//find index of smallest
		int min = i;
		for(int j = i; j<length; j++){
			if(numbers[min] > numbers[j]) min =j;
		}

		//change smalest
		int change = numbers[i];
		numbers[i] = numbers[min];
		numbers[min] = change;
	}

	numbers[length-1] = numbers[length-2]+3;
}

/*##############################################################################
# coutn how many are one and tree apart
##############################################################################*/
int findDistance(int *numbers, int length){
	int one = 0, three = 0;
	int disance;
	//for eacht element
	for(int i = 0; i<length-1; i++){
		disance = numbers[i+1] - numbers[i];
		switch (disance){
			case 1:
				one++;
				break;
			case 3:
				three++;
				break;
		}
	}

	return one*three;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int lineNumbers = numberOfLines(filename)+2;
	if(!lineNumbers) return 1;

	//get file as an array
	int *numbers = new int[lineNumbers];
	int res = loadFileInArray(filename, numbers);
	if(!res) return 1;

	//execute search
	sortNumbers(numbers, lineNumbers);

	//calculate distances
	res = findDistance(numbers, lineNumbers);
	cout << "sum 1 and 3 Distances: " << res << "\n";

	delete numbers; 

	return 0;
}