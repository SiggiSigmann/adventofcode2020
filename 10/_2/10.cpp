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

		cout << "Number of Adapters: " << ruleCount << '\n';

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

/*##############################################################################
# sort numbers from smal to big
##############################################################################*/
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
# calc posibilities within a given branch
##############################################################################*/
int calcBranchCombinations(int *numbers, int start, int stop){
	int res = 0;
	//ceck if goal is reached
	if(start == stop){
		return 1;
	}

	//check if a new branch can be reached
	int startValue = numbers[start];
	for(int i = start+1; i<=stop; i++){
		if(numbers[i]<=(startValue+3)){
			res += calcBranchCombinations(numbers, i, stop);
		}
	}

	//return result
	return res;
}

/*##############################################################################
# find how many branches exists per number and calculate posibilities form there
# on until they merge again
##############################################################################*/
long long int findCombinations(int *numbers, int length){
	//count branches
	int *branch = new int[length];

	//count branches for every entry
	for(int i = 0; i<length; i++){
		int countBranch = 0;
		for(int j = i+1; j<length; j++){
			if(numbers[j]<=(numbers[i]+3)) countBranch++;
		}
		branch[i] = countBranch;
	}

	//find index where banch starts and merge completly
	int start = 0;
	int lastItem = 0;
	bool startFound = 0;

	long long int res = 1;

	//find where branches begin / stops
	for(int i = 0; i<length; i++){
		if(startFound){
			//within a branch
			if(branch[i] == 1){
				//found end of a branch. Frome here ther is only one way to go
				int toMul = calcBranchCombinations(numbers, start, lastItem+i-1);
				res *= toMul;
				startFound = 0;
			}

		}else{
			if(branch[i] != 1){
				//found begin of a branch
				start = i;
				startFound = 1;
			}
		}
		lastItem = branch[i];
	}

	delete branch;

	return res;
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

	//execute sorting
	sortNumbers(numbers, lineNumbers);

	long long int  resl = findCombinations(numbers, lineNumbers);
	cout << "Combinations: " << resl << "\n";

	delete numbers; 

	return 0;
}