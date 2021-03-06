#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <bitset>

using namespace std;

/*##############################################################################
//store amount an color containd in a bag
##############################################################################*/
struct Contains{
	int amount;
	string color;
};

/*##############################################################################
//store rule for a color
##############################################################################*/
struct Rules{
	string color;
	int contains;
	Contains *containdBags = NULL;
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

		cout << "Number of Rules: " << ruleCount << '\n';

		inputFile.close();	
	}

	return ruleCount;
}

/*##############################################################################
# loads each line and put it in the corresponding group array
##############################################################################*/
int loadFileInArray(string fileName, Rules *rules){
	string inputLine;
	ifstream inputFile (fileName);

	if (inputFile.is_open()){
		int start = 0, stop = 0;

		//convert line into roul
		for(int i=0; getline(inputFile, inputLine);i++){
			start = 0;
			stop = 0;

			//extract color of the bag
			stop = inputLine.find("bags contain")-1;
			rules[i].color = inputLine.substr(start, stop-start);

			//count number of different bags 
			start = stop + 14;
			int ruleNumber  = 1;
			int countOffset = inputLine.find(",", start);
			while(countOffset != string::npos){
				ruleNumber++;
				countOffset++;
				countOffset = inputLine.find(",", countOffset);
			}

			//create array for contained bags
			rules[i].contains = ruleNumber;
			rules[i].containdBags = new Contains[rules[i].contains];
			
			//add first containd bag
			//get namount
			stop = inputLine.find(" ", start);
			if(inputLine.substr(start, 2)== "no"){
				rules[i].containdBags[0].amount = 0;
			}else{
				rules[i].containdBags[0].amount = stoi(inputLine.substr(start, stop-start));
			}

			//get color
			start = stop+1;
			stop = inputLine.find(" bag", start);
			rules[i].containdBags[0].color = inputLine.substr(start, stop-start);
			start = stop+4;

			stop = inputLine.find(",", start);

			//add left containd bag
			if(stop != string::npos){
				for(int j = 1; stop != string::npos && j < ruleNumber; j++){
					//get namount
					start = stop+2;
					stop = inputLine.find(" ", start);
					rules[i].containdBags[j].amount = stoi(inputLine.substr(start, stop-start));

					//get color
					start = stop+1;
					stop = inputLine.find(" bag", start);
					rules[i].containdBags[j].color = inputLine.substr(start, stop-start);

					//find next
					start = stop + 4;
					stop = inputLine.find(",", start);
				}

			}
			
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# calculate recursively the amount of bags contind in colorToFind bag.
##############################################################################*/
int golenBagFinder(Rules *rules, int length, string colorToFind){
	int res =0;

	//itterate over rules and try to finde needed collor
	for(int i = 0; i<length; i++){
		
		//find actual color
		if(rules[i].color == colorToFind){

			//claculate how many bags are containd in this one
			for(int j = 0; j<rules[i].contains; j++){
				
				// if no more bags are contained
				if(rules[i].containdBags[j].amount == 0){
					return 1;
				}

				//how many bags are containd in the containd one of this one
				int add = golenBagFinder(rules, length, rules[i].containdBags[j].color);

				//calculate current amount of bags
				res += add * rules[i].containdBags[j].amount;
			}
		}


	}

	return res+1;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int ruleNumber = numberOfLines(filename);
	if(!ruleNumber) return 1;

	//get file as an array
	Rules *rules = new Rules[ruleNumber];
	int res = loadFileInArray(filename, rules);
	if(!res) return 1;

	string* alreadyIncluded = new string[ruleNumber];
	cout << golenBagFinder(rules, ruleNumber, "shiny gold")-1 << "\n";

	for(int i = 0; i<ruleNumber; i++){
		if(rules[i].containdBags) delete rules[i].containdBags;
	}
	delete rules;
	delete alreadyIncluded; 

	return 0;
}