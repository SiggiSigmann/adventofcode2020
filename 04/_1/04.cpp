#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*##############################################################################
# depicts a database 
# byr (Birth Year)
# iyr (Issue Year)
# eyr (Expiration Year)
# hgt (Height)
# hcl (Hair Color)
# ecl (Eye Color)
# pid (Passport ID)
# cid (Country ID)
##############################################################################*/
struct Passport  {
	string byr;
	string iyr;
	string eyr;
	string hgt;
	string hcl;
	string ecl;
	string pid;
	string cid;
} ;


/*##############################################################################
# counts number of entires in given file
##############################################################################*/
int numberOfEntries(string fileName){
	int lineCount = 0;

	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		//count lines
		while (getline(inputFile, inputLine)){
			if(inputLine.empty()) lineCount++;
		}
		inputFile.close();

		lineCount++;	
	}

	cout << "Number of Etries: " << lineCount << '\n';

	return lineCount;
}

/*##############################################################################
# loads each entry in the file in a Passport array
# byr (Birth Year)
# iyr (Issue Year)
# eyr (Expiration Year)
# hgt (Height)
# hcl (Hair Color)
# ecl (Eye Color)
# pid (Passport ID)
# cid (Country ID)
##############################################################################*/
int loadFileInArray(string fileName, Passport *passports, int length){
	string inputLine;
	ifstream inputFile (fileName);
	if (inputFile.is_open()){
		int passport = 0;

		//itereate over file and fille array
		while(passport<length && getline(inputFile, inputLine)){
			if(inputLine.empty()){
				passport++;
				continue;
			}

			//split string an fille Passport entry
			int endoffset = inputLine.find(":");
			int start = 0;
			string key = "", value = "";
			while(endoffset != string::npos){
				key = inputLine.substr(start, endoffset-start);
				
				start = endoffset+1;
				endoffset = inputLine.find(" ", start);
				
				if(endoffset == string::npos) endoffset = inputLine.length();
				value = inputLine.substr(start, endoffset-start);

				//write key value in Passport entry
				if(key == "byr"){
					passports[passport].byr = value;
				}else if(key == "iyr"){
					passports[passport].iyr = value;
				}else if(key == "eyr"){
					passports[passport].eyr = value;
				}else if(key == "hgt"){
					passports[passport].hgt = value;
				}else if(key == "hcl"){
					passports[passport].hcl = value;
				}else if(key == "ecl"){
					passports[passport].ecl = value;
				}else if(key == "pid"){
					passports[passport].pid = value;
				}else if(key == "cid"){
					passports[passport].cid = value;
				}

				start = endoffset+1;
				endoffset = inputLine.find(":", start-1);
			}
		}

		inputFile.close();

		return 1;
	}
	return 0;
}

/*##############################################################################
# checks each entry in the Passport array if each key has a value
# byr (Birth Year)
# iyr (Issue Year)
# eyr (Expiration Year)
# hgt (Height)
# hcl (Hair Color)
# ecl (Eye Color)
# pid (Passport ID)
# cid (Country ID)
##############################################################################*/
int processPassport(Passport *entries, int length){
	int accepted = 0;

	for(int i = 0; i<length; i++){

		if(entries[i].byr.empty()){
			continue;
		}
		if(entries[i].iyr.empty()){
			continue;
		}
		if(entries[i].eyr.empty()){
			continue;
		}
		if(entries[i].hgt.empty()){
			continue;
		}
		if(entries[i].hcl.empty()){
			continue;
		}
		if(entries[i].ecl.empty()){
			continue;
		}
		if(entries[i].pid.empty()){
			continue;
		}

		accepted++;
	}

	return accepted;
}

int main(){
	string filename = "../input.txt";

	//get numbers of enties
	int entrieNumber = numberOfEntries(filename);
	if(!entrieNumber) return 1;

	//get file as an array
	Passport *passports = new Passport[entrieNumber];
	int res = loadFileInArray(filename, passports, entrieNumber);
	if(!res) return 1;

	//check entries
	res = processPassport(passports, entrieNumber);
	if(!res) return 1;

	cout << "Number of accepted: " << res <<"\n";

	delete passports;

	return 0;
}