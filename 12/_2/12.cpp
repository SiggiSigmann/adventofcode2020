#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

/*##############################################################################
# enum for different operations
##############################################################################*/
enum Direction{
	N = 0, 
	E = 1,
	S = 2,
	W = 3,
	L,
	R,
	F
};

/*##############################################################################
# store oparation and parameter
##############################################################################*/
struct Instruction{
	int amount;
	Direction direction;
};


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

		cout << "Number of Instructions: " << ruleCount << '\n';

		inputFile.close();	
	}

	return ruleCount;
}

/*##############################################################################
# loads each line in operations array
##############################################################################*/
int loadFileInArray(string fileName, Instruction *instr){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert line into long long int
		for(int i=0; getline(inputFile, inputLine);i++){
			char c = inputLine.at(0);
			if(c == 'N'){
				instr[i].direction = N;
			}else if(c == 'S'){
				instr[i].direction = S;
			}else if(c == 'E'){
				instr[i].direction = E;
			}else if(c == 'W'){
				instr[i].direction = W;
			}else if(c == 'L'){
				instr[i].direction = L;
			}else if(c == 'R'){
				instr[i].direction = R;
			}else if(c == 'F'){
				instr[i].direction = F;
			}
				
			instr[i].amount = stoi(inputLine.substr(1, inputLine.length()-1));
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# rotate waypoints (x, y) in rotate direction
##############################################################################*/
void rotate(Direction rotate, int amount,int *x, int * y){
	int steps = amount / 90;

	for(int i = 0; i<steps; i++){
		if(rotate == R){
			int save = *y;
			*y = 0-*x;
			*x = save;
		}else{
			int save = *x;
			*x = 0-*y;
			*y = save;
		}
	}
}

int calcDistance(Instruction *instr, int lineNumbers){
	//waypoint
	int directionWayY = 1;
	int directionWayX = 10;

	//ship position
	int shipX = 0;
	int shipY = 0;

	//process instructions
	for(int i = 0; i<lineNumbers; i++){
		switch(instr[i].direction){
			case N:
				directionWayY += instr[i].amount;
				break;
			case S:
				directionWayY-= instr[i].amount;
				break;
			case E:
				directionWayX += instr[i].amount;
				break;
			case W:
				directionWayX -= instr[i].amount;
				break;
			case L:
				rotate(L, instr[i].amount, &directionWayX, &directionWayY);
				break;
			case R:
				rotate(R, instr[i].amount, &directionWayX, &directionWayY);
				break;
			case F:
				for(int j = 0; j<instr[i].amount; j++){
					shipX += directionWayX;
					shipY += directionWayY;
				}
				break;
		}
	}

	return (abs(shipX)+abs(shipY));
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int lineNumbers = numberOfLines(filename);
	if(!lineNumbers) return 1;

	//get file as an array
	Instruction *instr = new Instruction[lineNumbers];
	int res = loadFileInArray(filename, instr);
	if(!res) return 1;

	//process instructions and calculate distance
	res = calcDistance(instr, lineNumbers);
	cout << res << "\n";

	delete instr; 

	return 0;
}