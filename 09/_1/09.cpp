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
int loadFileInArray(string fileName, long long int *numbers){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert line into long long int
		for(int i=0; getline(inputFile, inputLine);i++){
			numbers[i] = stoll(inputLine);
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# find sum-pair in array, starting bay indexToFindValue-preamble till indexToFindValue
##############################################################################*/
int findePair(long long int *numbers, int legth, int preamble, int indexToFindValue){
	int startidx = indexToFindValue -preamble;
	int sumToFind = numbers[indexToFindValue];
	
	//find sum pair by trying each combination
 	for(int i = startidx; i<(indexToFindValue-1); i++){
		for(int j = i+1; j<(indexToFindValue) ; j++){
			if((numbers[i]+numbers[j]) == sumToFind) return 1;
		}
	}
	return 0;
}

/*##############################################################################
# check each element in the array
##############################################################################*/
int findWrongNumber(long long int *numbers, int legth, int preamble){
	for(int i = preamble; i<legth; i++){
		int res = findePair(numbers,legth,preamble,i);
		//return if no sum-pair was found
		if(!res) return numbers[i];
	}
	return 0;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int lineNumbers = numberOfLines(filename);
	if(!lineNumbers) return 1;

	//get file as an array
	long long int *numbers = new long long int[lineNumbers];
	int res = loadFileInArray(filename, numbers);
	if(!res) return 1;

	//execute search
	res = findWrongNumber(numbers, lineNumbers, 25);
	cout << "Broken number: " << res << "\n";

	delete numbers; 

	return 0;
}