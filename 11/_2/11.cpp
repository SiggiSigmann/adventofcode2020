#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

/*##############################################################################
# counts number of lines in given file and line length
##############################################################################*/
int numberOfLines(string fileName, int *lineLength){
	int ruleCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine)){
			if(!ruleCount) *lineLength = inputLine.length();
			ruleCount++;
		}
		cout << "Number of Lines: " << ruleCount << '\n';
		cout << "lines: " << *lineLength << '\n';

		inputFile.close();	
	}

	return ruleCount;
}

/*##############################################################################
# loads each line in operations array
# empty Seat = 1, full seat = 0, flor = 2
##############################################################################*/
int loadFileInArray(string fileName, char **numbers){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert line into long long int
		for(int i=0; getline(inputFile, inputLine);i++){
			for(int j= 0; j < inputLine.length(); j++){
				if(inputLine.at(j) == 'L'){
					numbers[i][j] = 1;
				}else if(inputLine.at(j) == '#'){
					numbers[i][j] = 0;
				}else{
					numbers[i][j] = 2;
				}
			}
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# find next chair in sight
##############################################################################*/
int findNext(char **numbers, int lineNumbers, int lineLength, int curx, int cury, int setpx, int stepy){
	int x = curx, y = cury;
	x += setpx;
	y += stepy;
	//check if out of bounze
	while((0<=x)&&(x<lineNumbers)&&(0<=y)&&(y<lineLength)){
		//floor was found continue one step ahead
		if(numbers[x][y] == 2){
			x += setpx;
			y += stepy;

			continue;
		}

		//return seat
		return numbers[x][y];
	}
	return 2;
}

void processStep(char **numbers, int lineNumbers, int lineLength, char** target){
	//for each element
	for (int i = 0; i < lineNumbers; i++){
		for (int j = 0; j < lineLength; j++){
			//if flore => skip
			if(numbers[i][j]==2) continue;

			//finde seats around this one
			char found[8] = {2,2,2,2,2,2,2,2};
			found[0] = findNext(numbers, lineNumbers, lineLength, i, j, -1, -1);
			found[1] = findNext(numbers, lineNumbers, lineLength, i, j, -1, 0);
			found[2] = findNext(numbers, lineNumbers, lineLength, i, j, -1, +1);
			found[3] = findNext(numbers, lineNumbers, lineLength, i, j, 0, -1);
			found[4] = findNext(numbers, lineNumbers, lineLength, i, j, 0, +1);
			found[5] = findNext(numbers, lineNumbers, lineLength, i, j, 1, -1);
			found[6] = findNext(numbers, lineNumbers, lineLength, i, j, 1, 0);
			found[7] = findNext(numbers, lineNumbers, lineLength, i, j, 1, +1);

			//count how many are occupied
			int occup = 0;
			for(int k = 0; k<8; k++){
				if(found[k] == 2) continue;
				if(found[k] == 0) occup++;
			}

			//check if seats around are empty
			if(occup == 0){
				target[i][j] = 0;
				continue;
			}

			//check if too many seats are occupied
			if(occup>4) target[i][j] = 1;
		}
	}
}

/*##############################################################################
# compare numbers and target array
##############################################################################*/
int compare(char **numbers, int lineNumbers, int lineLength, char** target){
	for(int i = 0; i < lineNumbers; i++){
		for (size_t j = 0; j < lineLength; j++){
			if(target[i][j] != numbers[i][j]) return 0;
		}
	}
	return 1;
}

/*##############################################################################
# process array and count empty seats
##############################################################################*/
int processArray(char **numbers, int lineNumbers, int lineLength){
	char **target = new char*[lineNumbers];
	for(int i = 0; i < lineNumbers; i++){
		target[i] = new char[lineLength];
		for (int j = 0; j < lineLength; j++){
			target[i][j] = numbers[i][j];
		}
	}

	//process array until no changes
	do{
		//copy targer to number
		for(int i = 0; i < lineNumbers; i++){
			for (int j = 0; j < lineLength; j++){
				numbers[i][j] = target[i][j];
			}
		}

		//process next step		
		processStep(numbers, lineNumbers, lineLength, target);

		//check if another step is needed
	}while(!compare(numbers, lineNumbers, lineLength, target));

	//count empty seats
	int seats = 0;
	for(int i = 0; i < lineNumbers; i++){
		for (int j = 0; j < lineLength; j++){
			if(target[i][j] == 0){
				seats++;
			}
		}
	}

	for(int i = 0; i < lineNumbers; i++){
		delete target[i];
	}
	delete target; 

	return seats;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int lineLength;
	int lineNumbers = numberOfLines(filename, &lineLength);
	if(!lineNumbers) return 1;

	//get file as an array
	char **numbers = new char*[lineNumbers];
	for(int i = 0; i < lineNumbers; i++){
		numbers[i] = new char[lineLength];
	}
	int res = loadFileInArray(filename, numbers);
	if(!res) return 1;

	//calculate empty seats after they stabelice
	res = processArray(numbers, lineNumbers, lineLength);
	cout << "Empty seats: "<< res << "\n";

	for(int i = 0; i < lineNumbers; i++){
		delete numbers[i];
	}
	delete numbers;

	return 0;
}