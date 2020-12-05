#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

/*##############################################################################
# struct define a seat
##############################################################################*/
struct Seat{
	int row;
	int column;
	int seatID;
};

/*##############################################################################
# counts number of lines in given file
##############################################################################*/
int numberOfLines(string fileName){
	int lineCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine))lineCount++;

		cout << "Number of Lines: " << lineCount << '\n';
		inputFile.close();	
	}

	return lineCount;
}

/*##############################################################################
# loads each line of the file in a string array
##############################################################################*/
int loadFileInArray(string fileName, string *lines){
	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		for(int i=0; getline(inputFile, inputLine);i++){
			lines[i] = inputLine;
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# calculates seat and save it in seat array
# return the biggest seatID
##############################################################################*/
int processSeats(string *lines, int lineNumber, Seat *seat){
	int maxID = 0;

	for(int i = 0;i<lineNumber;i++){
		int column = 0, row = 0;
		int addToColumn = 4;
		int addToRow = 64;

		for(int j = 0;j<lines[i].length();j++){
			if(j<7){
				if(lines[i].at(j)=='B'){
					row += addToRow;
				}
				addToRow /= 2;
			}else{
				if(lines[i].at(j)=='R'){
					column += addToColumn;
				}
				addToColumn /= 2;
			}
			
		}

		seat[i].column = column;
		seat[i].row = row;
		seat[i].seatID = row*8 + column;

		if(maxID<seat[i].seatID) maxID = seat[i].seatID;
	}

	return maxID;
}

/*##############################################################################
# sorts seat array from smallest to biggest seatID
##############################################################################*/
void sortSeats(Seat *seat, int lineNumber){
	unsigned int min;
	int changeID = 0;
	int sorted = 0;
	int done = 0;
	while(sorted < lineNumber-1){
		min = 0-1;
		
		for(int i = sorted; i<lineNumber; i++){
			if(min > seat[i].seatID){
				min = seat[i].seatID;
				changeID = i;
			}
		}

		Seat tochange = seat[changeID];
		seat[changeID] = seat[sorted];
		seat[sorted] = tochange;
		sorted++;
	}
}

/*##############################################################################
# find missing seat in list and return its seatID
##############################################################################*/
int findSeat(Seat *seat, int lineNumber){
	for(int i = 1; i<(lineNumber-1); i++){
		if((seat[i+1].seatID - seat[i].seatID) == 2){
			return seat[i].seatID+1;
		}
	}
	return 0;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int charsPerLine = 0;
	int lineNumber = numberOfLines(filename);
	if(!lineNumber) return 1;

	//get file as an array
	string *lines = new string[lineNumber];
	int res = loadFileInArray(filename, lines);
	if(!res) return 1;

	//calulate seats
	Seat *seat = new Seat[lineNumber];
	res = processSeats(lines, lineNumber, seat);

	//sort seats
	sortSeats(seat, lineNumber);

	//find missing seat
	res = findSeat(seat, lineNumber);

	cout << "my SeatID: " << res << "\n";

	delete lines;
	delete seat;

	return 0;
}