#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

/*Day 4: Passport Processing
 * Part 1:
 * Problem: Given passport entries consisting of key-value pairs and separated by empty lines
 * count the number of valid passports. A passport is valid if every key (cid optional) is available.
 *
 * Constraint: assuming that each key field seen is a valid key. If not, a const unordered_set should be created consisting of the valid keys
 *
 * Part 2:
 * Problem: Keys now need to be validated by their values. Use the following criteria:
 * --byr (Birth Year) - four digits; at least 1920 and at most 2002.
 * --iyr (Issue Year) - four digits; at least 2010 and at most 2020.
 * --eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
 * --hgt (Height) - a number followed by either cm or in:
	--If cm, the number must be at least 150 and at most 193.
	--If in, the number must be at least 59 and at most 76.
 * --hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
 * --ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
 * --pid (Passport ID) - a nine-digit number, including leading zeroes.
 * --cid (Country ID) - ignored, missing or not.
*/

bool IsNum(const string &value){
	for(const char &c: value){
		if(!isdigit(c))
			return false;
	}
	return true;
}

bool IsHexa(const string &value){
	for(const char &c: value){
		if(!isdigit(c) && (c < 'a' || c > 'f'))
			return false;
	}
	return true;
}

bool Valid(string key, string value){
	if(key == "byr"){
		cout << "byr" << endl;
		if(IsNum(value)){
			int num = stoi(value);
			return num >= 1920 && num <= 2002;
		}
		else{
			return false;
		}
	}
	else if(key == "iyr"){
		cout << "iyr" << endl;
		if(IsNum(value)){
			int num = stoi(value);
			return num >= 2010 && num <= 2020;
		}
		else{
			return false;
		}
	}
	else if(key == "eyr"){
		if(IsNum(value)){
			int num = stoi(value);
			return num >= 2020 && num <= 2030;
		}
		else{
			return false;
		}
	}
	else if(key == "hgt"){
		if(value.size() < 4) return false;
		string metric = value.substr(value.size()-2);
		if(IsNum(value.substr(0,value.size()-2))){
			int num = stoi(value.substr(0,value.size()-2));
			if(metric == "cm"){
				return num >= 150 && num <= 193;
			}
			else if(metric == "in"){
				return num >= 59 && num <= 76;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else if(key == "hcl"){
		return value[0] == '#' && IsHexa(value.substr(1));
	}
	else if(key == "ecl"){
		unordered_set<string> colors({"amb","blu","brn","gry","grn","hzl","oth"});
		return colors.find(value) != colors.end();
	}
	else if(key == "pid"){
		return IsNum(value) && value.size() == 9;
	}
	else{
		return false;
	}
}

int main(){
	ifstream input_file("day4.txt");
	int count = 0;
	string passport_line;
	//loop per line of file
	unordered_set<string> seen_keys;
	while(getline(input_file,passport_line)){
		cout << passport_line << endl;
		//If end of passport is reached, 
		//check if valid then move onto next passport
		if(passport_line.empty()){
			count += seen_keys.size() == 7;
			cout << seen_keys.size() << " keys seen; " << count << endl;
			seen_keys.clear();
			continue;
		}
		stringstream ss(passport_line);
		string passport_pair;
		while(ss >> passport_pair){
			string key = passport_pair.substr(0,3);
			string value = passport_pair.substr(4);
			if(Valid(key,value))
				seen_keys.insert(key);
		}
	}
	count += seen_keys.size() == 7;
	cout << "This is the count: " << count << endl;
	input_file.close();
	return 0;
}
