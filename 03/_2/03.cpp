#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*##############################################################################
# counts number of lines in given file
##############################################################################*/
int numberOfLines(string fileName, int *charPerLine){
	int lineCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine)){
			if(!lineCount) *charPerLine = inputLine.length();
			lineCount++;
		}

		cout << "Number of Lines: " << lineCount << '\n';
		cout << "Char per lines: " << *charPerLine << '\n';
		inputFile.close();	
	}

	return lineCount;
}

/*##############################################################################
# loads each char per line of the file in a string array
##############################################################################*/
int loadFileInArray(string fileName, int **lines){
	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		for(int i=0; getline(inputFile, inputLine);i++){
			for(int j=0; j<inputLine.length(); j++){
				//prepare array 1 -> tree, 0 -> nothing
				lines[i][j] = inputLine.at(j) == '#' ? 1 : 0;
			}
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# count how many trees will be hit by the way
##############################################################################*/
int processWay(int **entries, int length, int depth, int stepx, int stepy){
	int trees = 0;
	int x = 0, y = 0; //x => right, y => down

	while(y < length){
		//check if location is a tree
		if(entries[y][x]) trees++;

		//calculate next step
		y += stepy;
		x += stepx;
		x %= depth;
	}

	return trees;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int charsPerLine = 0;
	int lineNumber = numberOfLines(filename, &charsPerLine);
	if(!lineNumber || !charsPerLine) return 1;

	//get file as an array
	int **lines = new int*[lineNumber];
	for(int i = 0; i<lineNumber; i++){
		lines[i] = new int[charsPerLine];
	}
	int res = loadFileInArray(filename, lines);
	if(!res) return 1;

	//process ways
	
	long long int res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0;
	//Right 1, down 1.
	res1 = processWay(lines, lineNumber, charsPerLine, 1, 1);
	//Right 3, down 1.
	res2 = processWay(lines, lineNumber, charsPerLine, 3, 1);
	//Right 5, down 1.
	res3 = processWay(lines, lineNumber, charsPerLine, 5, 1);
	//Right 7, down 1.
	res4 = processWay(lines, lineNumber, charsPerLine, 7 ,1);
	//Right 1, down 2.
	res5 = processWay(lines, lineNumber, charsPerLine, 1, 2);

	cout << res1 << " " << res2 << " " << res3 << " " << res4 << " " << res5 << "\n";

	long long int multiply = res1 * res2 * res3 * res4 * res5;
	
	cout << "trees hit (multiplied): " << multiply << "\n";




	return 0;
}