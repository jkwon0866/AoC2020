#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

/* Day 2: Password Philosophy
 * Part 1:
 * Problem: Output the number of valid passwords in the list, where the numbers next to the character is the range of valid counts
 * 
 * Part 2:
 * Problem: The numbers now represent the positions (1-indexed) that the character can be in. It must be in exactly one of these places.
*/

bool ValidRangePass(const int &low, const int &high, char &letter, string &password){
	int count = 0;
	for(char c: password) count += (c == letter);
	return count >= low && count <= high;
}

bool ValidPositionPass(const int &pos1, const int &pos2, char &letter, string &password){
	return password[pos1-1] == letter ^ password[pos2-1] == letter;
}

int main(){
	ifstream input_file("day2.txt");
	string num_range, letter, password;
	//Part 1:
	int count = 0;
	while(input_file >> num_range >> letter >> password){
		int dash_pos = num_range.find("-");
		int num1 = stoi(num_range.substr(0,dash_pos));
		int num2 = stoi(num_range.substr(dash_pos+1));
		//count += ValidRangePass(num1, num2, letter[0], password);
		count += ValidPositionPass(num1, num2, letter[0], password);
	}
	input_file.close();
	cout << "number of valid passwords:" << count << endl;
	return 0;
}
