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

Direction rotate(Direction old, Direction rotate, int amount){
	//cout << old << "\n";
	if(rotate == R){
		int steps = amount / 90;
		int res = (int)old + steps;
		//cout << "->" << res << " " << steps <<"\n";
		//cout << "=> " << old << " " << res %4 << "\n";
		return (Direction) (res %4);
	}else{
		int steps = amount / 90;
		int res = (int)old - steps;

		//cout << amount << "\n";
		//cout << "->" << old << " " << res << " " << steps <<"\n";
		if(res < 0) res += 4;
		//cout << "=> " << old << " " << res %4 << "\n";//cout << "=> "  << old << " " << res %4 << "\n";
		return (Direction) (res %4);
	}
}

int calcDistance(Instruction *instr, int lineNumbers){
	Direction d = E;
	//cout << d << "\n";
	int directionX = 0;
	int directionY = 0;
	for(int i = 0; i<lineNumbers; i++){
		switch(instr[i].direction){
			case N:
				directionY += instr[i].amount;
				break;
			case S:
				directionY -= instr[i].amount;
				break;
			case E:
				directionX += instr[i].amount;
				break;
			case W:
				directionX -= instr[i].amount;
				break;
			case L:
				d = rotate(d, L, instr[i].amount);
				break;
			case R:
				d = rotate(d, R, instr[i].amount);
				break;
			case F:
				if(d == N){
					directionY += instr[i].amount;
				}else if(d == S){
					directionY -= instr[i].amount;
				}else if(d == E){
					directionX += instr[i].amount;
				}else if(d == W){
					directionX -= instr[i].amount;
				}
				break;
		}

		//cout << directionX << " " << directionY << "\n";
	}

	return (abs(directionX)+abs(directionY));
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

	res = calcDistance(instr, lineNumbers);
	cout << res << "\n";

	delete instr; 

	return 0;
}