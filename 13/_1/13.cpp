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
		bool first = 1;
		while (getline(inputFile, inputLine)){
			if(first){
				first = 0;
				continue;
			}
			for(int i = 0; i< inputLine.length(); i++){
				if(inputLine.at(i) == ',') ruleCount++;
			}
			ruleCount++;
			
		}
		cout << "Number of Busses: " << ruleCount << '\n';

		inputFile.close();	
	}

	return ruleCount;
}

/*##############################################################################
# loads each line in bus array
##############################################################################*/
int loadFileInArray(string fileName, int *bus, int *timeStamp){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert lines
		for(int i=0; getline(inputFile, inputLine);i++){
			if(!i){
				//frist line holds timestamp
				*timeStamp = stoi(inputLine);
				cout << "Timestamp: " << *timeStamp << '\n';
				continue;
			}

			int start = 0;
			int offset = inputLine.find(',');
			int idx = 0;

			//load comma seperated list
			while(offset !=  string::npos){
				//check if entry in list exists
				string sub = inputLine.substr(start, offset-start);
				if(sub != "x"){
					bus[idx] = stoi(inputLine.substr(start, offset-start));
				}else{
					bus[idx] = 0;
				}

				//find next entry
				idx++;
				start = offset+1;
				offset = inputLine.find(',', start);
			}
			bus[idx] = stoi(inputLine.substr(start));
			
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# calc next bus and time to wait
##############################################################################*/
int calcNextBus(int *busses, int busNumber, int timestamp){
	//get minimal waitingtime
	int min = busses[0]-(timestamp% busses[0]);
	int minBus = 0;

	//check each bus
	for(int i = 1; i<busNumber; i++){
		//skip empty values
		if(!busses[i]) continue;

		//calc waitingtime and compare
		int tempMin = busses[i]-(timestamp% busses[i]);
		if(tempMin<min){
			min = tempMin;
			minBus = i;
		}
	}

	return busses[minBus]*min;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int busNumber = numberOfLines(filename);
	if(!busNumber) return 1;

	//get file as an array
	int *busses = new int[busNumber];
	int timestamp = 0;
	int res = loadFileInArray(filename, busses, &timestamp);
	if(!res) return 1;

	//calculate result
	res = calcNextBus(busses, busNumber, timestamp);
	cout << "BusID times waitingtime: " << res << "\n";

	delete busses; 

	return 0;
}