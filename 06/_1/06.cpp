#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <bitset>

using namespace std;


/*##############################################################################
# counts number of lines in given file and fine the biggest group
##############################################################################*/
int numberOfLines(string fileName, int *maxGroupSize){
	int groupCount = 0;
	int countGroupSize = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine)){
			if(inputLine.empty()){
				groupCount++;
				if(*maxGroupSize < countGroupSize) *maxGroupSize = countGroupSize;
				countGroupSize = 0;
			}else{
				countGroupSize++;
			}
		}

		groupCount++;

		cout << "Number of Groups: " << groupCount << '\n';
		cout << "Biggest Group: " << *maxGroupSize << '\n';
		inputFile.close();	
	}

	return groupCount;
}

/*##############################################################################
# loads each line and put it in the corresponding group array
##############################################################################*/
int loadFileInArray(string fileName, string **groups){
	string inputLine;
	ifstream inputFile (fileName);
	int groupCounter = 0;
	int personCounter = 0;

	if (inputFile.is_open()){
		for(int i=0; getline(inputFile, inputLine);i++){
			if(inputLine.empty()){
				groupCounter++;
				personCounter=0;
			}else{
				groups[groupCounter][personCounter] = inputLine;
				personCounter++;
			}
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# count how many answers are given per group and store this number in answers
##############################################################################*/
int processGroups(string **entries, int groupNumber, int maxGroupSize, int *answeres){
	string person;
	for(int i = 0; i < groupNumber; i++){
		//each answer is represented by a bit in this variable
		int givenAnsweres = 0;
		int countAnsweres = 0;
		
		for(int j = 0; j < maxGroupSize; j++){
			person = entries[i][j];
			
			if(!person.empty()){
				for(int k = 0; k < person.length(); k++){
					int anserID = (int)pow(2, person.at(k)-97);

					//check if answere is already given
					if(!(givenAnsweres & anserID)){
						countAnsweres++;
						givenAnsweres |= anserID;
					}
				}
			}
		}
		
		answeres[i] = countAnsweres;
	}
	
	return 1;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int maxGroupSize = 0;
	int groupNumber = numberOfLines(filename, &maxGroupSize);
	if(!groupNumber || !maxGroupSize) return 1;

	//get file as an array
	string **groups = new string*[groupNumber];
	for(int i = 0; i<groupNumber; i++){
		groups[i] = new string[maxGroupSize];
	}
	int res = loadFileInArray(filename, groups);
	if(!res) return 1;

	//process Groups
	int *anseres = new int[groupNumber];
	res = processGroups(groups, groupNumber, maxGroupSize, anseres);
	
	//sum group answers
	int sumGroupAnswers = 0;
	for(int i = 0; i< groupNumber; i++){
		sumGroupAnswers += anseres[i];
	}
	cout << "Answers: " << sumGroupAnswers << "\n";
	
	for(int i = 0; i<groupNumber; i++){
		delete groups[i];
	}
	delete groups;
	delete anseres;

	return 0;
}