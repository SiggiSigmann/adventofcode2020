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
# The next seven methods are checks rules for each entry
##############################################################################*/
//byr (Birth Year) - four digits; at least 1920 and at most 2002.
int byrCheck(string input){
	if(input.empty()) return 0;

	try{
		int i = std::stoi(input);
		if(!(1920 <= i && i <= 2002)) return 0;
	}catch (std::invalid_argument const &e){
		return 0;
	}

	return 1;
}

//iyr (Issue Year) - four digits; at least 2010 and at most 2020.
int iyrCheck(string input){
	if(input.empty()) return 0;
	
	try{
		int i = std::stoi(input);
		if(!(2010 <= i && i <= 2020)) return 0;
	}catch (std::invalid_argument const &e){
		return 0;
	}
	
	return 1;
}

//eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
int eyrCheck(string input){
	if(input.empty()) return 0;

	try{
		int i = std::stoi(input);
		if(!(2020 <= i && i <= 2030)) return 0;
	}catch (std::invalid_argument const &e){
		return 0;
	}

	return 1;
}

//hgt (Height) - a number followed by either cm or in:
// - If cm, the number must be at least 150 and at most 193.
// - If in, the number must be at least 59 and at most 76.
int hgtCheck(string input){
	if(input.empty()) return 0;

	int split = input.find("cm");
	if(split == string::npos){
		split = input.find("in");
		if(split == string::npos) return 0;
	}

	string height = input.substr(0, split);
	string unit = input.substr(split, input.length()-(split));

	try{
		int i = std::stoi(height);
		if(unit == "cm"){
			if(!(150 <= i && i <= 193)) return 0;
		}else{
			if(!(59 <= i && i <= 76)) return 0;
		}
		
	}catch (std::invalid_argument const &e){
		return 0;
	}

	return 1;
}

//(Hair Color) - a # followed by exactly six characters 0-9 or a-f
// ASCII values => 48->57 (0-9) and 97->102 (a-f)
int hclCheck(string input){
	if(input.empty()) return 0;

	int split = input.find("#");
	if(split == string::npos || split != 0) return 0;

	string color = input.substr(split+1, input.length()-(split+1));

	for(int i = 0; i < color.length(); i++){
		char c = color.at(i);
		if(!((48 <= c && c <=57) || (97 <= c && c <= 102))) return 0;
	}

	return 1;
}

//(Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
int eclCheck(string input){
	if(input.empty()) return 0;
	
	if(!(input == "amb" || input == "blu" || input == "brn" || input == "gry" || input == "grn" || input == "hzl" || input == "oth")){
		return 0;
	}

	return 1;
}

//(Passport ID) - a nine-digit number, including leading zeroes.
int pidCheck(string input){
	if(input.empty()) return 0;

	if(input.length() != 9) return 0;

	try{
		int i = std::stoi(input);
	}catch (std::invalid_argument const &e){
		return 0;
	}

	return 1;
}

/*##############################################################################
# checks each entry in the Passport array against the rules defined above
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

		if(!byrCheck(entries[i].byr)){
			continue;
		}
		if(!iyrCheck(entries[i].iyr)){
			continue;
		}
		if(!eyrCheck(entries[i].eyr)){
			continue;
		}
		if(!hgtCheck(entries[i].hgt)){
			continue;
		}
		if(!hclCheck(entries[i].hcl)){
			continue;
		}
		if(!eclCheck(entries[i].ecl)){
			continue;
		}
		if(!pidCheck(entries[i].pid)){
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
	
	delete passport;

	return 0;
}