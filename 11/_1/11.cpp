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
# process seat configuration and store it in target
##############################################################################*/
void processStep(char **numbers, int lineNumbers, int lineLength, char** target){
	int count = 0;

	//for every element
	for (int i = 0; i < lineNumbers; i++){
		for (int j = 0; j < lineLength; j++){
			count = 0;
			if(numbers[i][j]==2) continue;
			if(i == 0){
				//top row
				if(j == 0){
					//top left

					//check if all are empty
					if(numbers[i+1][j]*numbers[i][j+1]*numbers[i+1][j+1]){
						target[i][j] = 0;
						continue;
					}

					//no way to empty the seat
				}else if(j == lineLength-1){
					//top right

					//check if all are empty
					if(numbers[i+1][j]*numbers[i][j-1]*numbers[i+1][j-1]){
						target[i][j] = 0;
						continue;
					}

					//no way to empty
				}else{
					//topline

					//check if all are empty
					if(numbers[i][j-1]*numbers[i][j+1]*numbers[i+1][j]*
										numbers[i+1][j-1]*numbers[i+1][j+1]){
						target[i][j] = 0;
						continue;
					}

					//check if to many occupied
					if(!numbers[i][j-1]) count++;
					if(!numbers[i][j+1]) count++;
					if(!numbers[i+1][j]) count++;
					if(!numbers[i+1][j-1]) count++;
					if(!numbers[i+1][j+1]) count++;

					if(count > 3) target[i][j] = 1;
				}
			}else if(i == lineNumbers-1){
				//bottom line
				if(j == 0){
					//bottom left

					//check if all are empty
					if(numbers[i-1][j]*numbers[i-1][j+1]*numbers[i][j+1]){
						target[i][j] = 0;
						continue;
					}

					//no way to empty
				}else if(j == lineLength-1){
					//bottom right

					//check if all are empty
					if(numbers[i-1][j]*numbers[i][j-1]*numbers[i-1][j-1]){
						target[i][j] = 0;
						continue;
					}

					//no way to empty
				}else{
					//bottom line

					//check if all are empty
					if(numbers[i][j-1]*numbers[i][j+1]*numbers[i-1][j-1]*
										numbers[i-1][j]*numbers[i-1][j+1]){
						target[i][j] = 0;
						continue;
					}

					//check if to many occupied
					if(!numbers[i][j+1]) count++;
					if(!numbers[i][j-1]) count++;
					if(!numbers[i-1][j]) count++;
					if(!numbers[i-1][j+1]) count++;
					if(!numbers[i-1][j-1]) count++;

					if(count > 3) target[i][j] = 1;
				}
			}else{
				//middel
				if(j == 0){
					//middel right

					//check if all are empty
					if(numbers[i-1][j]*numbers[i+1][j]*numbers[i-1][j+1]*
										numbers[i][j+1]*numbers[i+1][j+1]){
						target[i][j] = 0;
						continue;
					}

					//check if to many occupied
					if(!numbers[i-1][j]) count++;
					if(!numbers[i+1][j]) count++;
					if(!numbers[i-1][j+1]) count++;
					if(!numbers[i][j+1]) count++;
					if(!numbers[i+1][j+1]) count++;

					if(count > 3) target[i][j] = 1;

				}else if(j == lineLength-1){
					//middel left

					//check if all are empty
					if(numbers[i-1][j]*numbers[i+1][j]*numbers[i-1][j-1]*
										numbers[i][j-1]*numbers[i+1][j-1]){
						target[i][j] = 0;
						continue;
					}

					//check if to many occupied
					if(!numbers[i-1][j]) count++;
					if(!numbers[i+1][j]) count++;
					if(!numbers[i-1][j-1]) count++;
					if(!numbers[i][j-1]) count++;
					if(!numbers[i+1][j-1]) count++;

					if(count > 3) target[i][j] = 1;

				}else{
					//middel
					
					//check if all are empty
					if(numbers[i-1][j+1]*numbers[i-1][j]*numbers[i-1][j-1]*
							numbers[i][j+1]*numbers[i][j-1]*
							numbers[i+1][j-1]*numbers[i+1][j]*numbers[i+1][j+1]){
						target[i][j] = 0;
						continue;
					}

					//check if to many occupied
					if(!numbers[i-1][j]) count++;
					if(!numbers[i+1][j]) count++;

					if(!numbers[i-1][j-1]) count++;
					if(!numbers[i][j-1]) count++;
					if(!numbers[i+1][j-1]) count++;

					if(!numbers[i-1][j+1]) count++;
					if(!numbers[i][j+1]) count++;
					if(!numbers[i+1][j+1]) count++;

					if(count > 3) target[i][j] = 1;
					
				}
			}
		}
	}
}

/*##############################################################################
# compare numbers and target array
##############################################################################*/
int compare(char **numbers, int lineNumbers, int lineLength, char** target){
	//cout <<" process "<< "\n";
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