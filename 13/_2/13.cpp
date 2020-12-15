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
int loadFileInArray(string fileName, int *bus){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int spacer = 0;

		//convert line into long long int
		for(int i=0; getline(inputFile, inputLine);i++){
			//skip timestamp in first line
			if(!i) continue;
			
			//load comma seperated list
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
# calc busses one minute apart
##############################################################################*/
long long int findBusSequence(int *busses, int busNumber){
	//startvalue
	long long int toAdd = busses[0];
	long long int targetTimeStamp = toAdd;

	//echt step, consider one more bus
	for(int i = 1; i<busNumber; i++){
		//skip bus if it dosn't exist
		if(!busses[i]) continue;

		//try to finde timestamp where each considerd busses are one step apart
		while((targetTimeStamp+i)%busses[i]){
			targetTimeStamp+=toAdd;
		}

		//each multible of the current BusIDs will be also a timestemp where
		//considerd busses departure one minit apart.
		toAdd *= busses[i];
	}

	return targetTimeStamp;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int busNumber = numberOfLines(filename);
	if(!busNumber) return 1;

	//get file as an array
	int *busses = new int[busNumber];
	int res = loadFileInArray(filename, busses);
	if(!res) return 1;

	//get sequence where each bus starts one minit apart
	long long int targetTimeStamp = findBusSequence(busses, busNumber);
	cout << "Sequence: " << targetTimeStamp << "\n";

	delete busses; 

	return 0;
}