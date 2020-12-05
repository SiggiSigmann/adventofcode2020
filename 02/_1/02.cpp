#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*##############################################################################
# depicts a database entry
##############################################################################*/
struct passwdEntry {
  int min;
  int max;
  char c;
  string passwd;
} ;

/*##############################################################################
# counts number of lines in given file
##############################################################################*/
int numberOfLines(string fileName){
	int lineCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		
		//count lines
		while (getline(inputFile, inputLine)) lineCount++;
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
			lines[i]= inputLine;
		}
		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# converts each entry in the string array into an entry for the passwdEntry array
##############################################################################*/
int convertStringArrayTOpasswdEntryArray(string *lines, passwdEntry *entries, int length){
	for(int i = 0; i<length; i++){

		//finds char which delimits the parameter and extract the parameter
		int end = lines[i].find("-");
		entries[i].min = stoi(lines[i].substr(0, end));

		//finds char which delimits the parameter and extract the parameter
		int start = end+1;
		end = lines[i].find(" ");
		entries[i].max = stoi(lines[i].substr(start, end));

		//finds char which delimits the parameter and extract the parameter
		start = end+1;
		end = lines[i].find(":");
		entries[i].c = lines[i].at(start);

		//finds char which delimits the parameter and extract the parameter
		start = end+2;
		end = lines[i].size();
		entries[i].passwd = lines[i].substr(start, end);
	}

	return 1;
}

/*##############################################################################
# check each entry if it fits the policy
##############################################################################*/
int checkEntries(passwdEntry *entries, int length){
	int correct = 0;
	for(int i = 0; i<length; i++){
		//get entry to process
		passwdEntry entry = entries[i];

		//iterates over string and count occurrence of char
		int occurrence = 0;
		int offset = entry.passwd.find(entry.c);
		while(offset !=  string::npos){
			occurrence ++;
			offset = entry.passwd.find(entry.c, offset+1);
		}

		//check occurrence of char
		if(entry.min <= occurrence && occurrence <= entry.max){
			correct++;
		}
	}
	return correct;
}

int main(){
	string filename = "../input.txt";

	//get numbers of line
	int lineNumber = numberOfLines(filename);
	if(!lineNumber) return 1;

	//get file as an array
	string *lines = new string[lineNumber];
	int res = loadFileInArray(filename, lines);
	if(!res) return 1;

	//convert lines to database entries
	passwdEntry *entries = new passwdEntry[lineNumber];
	res = convertStringArrayTOpasswdEntryArray(lines, entries, lineNumber);
	if(!res) return 1;

	//process entries
	res = checkEntries(entries, lineNumber);
	if(!res) return 1;

	cout << "correct passwors: " << res << "\n";

	delete lines;
	delete entries;

	return 0;
}