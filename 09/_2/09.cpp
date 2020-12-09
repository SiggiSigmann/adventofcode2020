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
		if(!res) return i;
	}
	return -1;
}

/*##############################################################################
# find continous set of Numbers that adds up to wrongNumber
##############################################################################*/
int findSetFrom(long long int *numbers, int wrongNumberIndex, int start){
	int sum = 0;

	//sum all numbers started by startvlaue till sum is bigger or exactly wrongNumberIndex
	for(int i = start; i<wrongNumberIndex; i++){
		sum += numbers[i];
		if(sum == numbers[wrongNumberIndex]) return i;
		if(sum >  numbers[wrongNumberIndex]) return -1;
	}
	return -1;
}

/*##############################################################################
# find sum set in numbers and add up min and max if one set was found
##############################################################################*/
int findSumSet(long long int *numbers, int wrongNumberIndex){
	for(int i = 0; i<wrongNumberIndex; i++){
		//find set
		int res = findSetFrom(numbers, wrongNumberIndex, i);

		//check if set was found
		if(res == -1) continue;

		//find min and max
		long long int min = 0x7FFFFFFFFFFFFFFF;
		long long int max = 0;
		for(int j = i; j<res; j++){
			if(min>numbers[j]) min = numbers[j];
			if(max<numbers[j]) max = numbers[j];
		}


		return (min+max);
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
	if(res < 0) return 1;
	cout << "Broken number: " << numbers[res] << "\n";

	//execute set scanning
	res = findSumSet(numbers, res);
	if(!res) return 1;
	cout << "Sum of the smalles and biggest: " << res << "\n";

	delete numbers; 

	return 0;
}