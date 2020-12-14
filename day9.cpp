#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

/* Day 9: Encoding Error
 * Part 1:
 * Problem: Find the first number that doesn't meet the requirement of two of the previous 25 numbers
 * summing to it.
 *
 * Part 2:
 * Problem: Determine the contiguous set of numbers in the list that sum to the invalid number,
 * then add the smallest and largest in this set.
*/

//Part 1
bool Valid(const long &num, const unordered_set<long> &preamble){
	for(const long &p: preamble){
		//cout << p << 
		if(preamble.find(num - p) != preamble.end())
			return true;
	}
	return false;
}

int main(){
	//Answer from part 1 was 400480901
	ifstream input_file("day9.txt");
	string num_str;
	long num;
	long sum = 0;
	deque<long> sequence;
	//bool found = false;
	while(sum != 400480901){
		if(sum < 400480901){
			input_file >> num_str;
			num = stol(num_str);
			sequence.push_front(num);
			sum += num;
		}
		else{
			sum -= sequence.back();
			sequence.pop_back();
		}
		cout << "num: " << num << endl;
		cout << "sum: " << sum << endl;
	}
	cout << "found the contiguous set: " << sum << endl;
	long min_num = LONG_MAX, max_num = 0;
	while(!sequence.empty()){
		min_num = min(sequence.back(), min_num);
		max_num = max(sequence.back(), max_num);
		sequence.pop_back();
	}
	cout << "min_num: " << min_num << endl;
	cout << "max_num: " << max_num << endl;
	cout << "two sum: " << min_num + max_num << endl;
	/*
	unordered_set<int> preamble;
	vector<int> sequence;
	for(int i = 0; i < 25; i++){
		input_file >> num_str;
		num = stoi(num_str);
		preamble.insert(num);
		sequence.push_back(num);
	}
	bool found = false;
	while(!found && input_file >> num_str){
		//cout << num_str << endl;
		num = stoi(num_str);
		found = !Valid(num,preamble);
		preamble.erase(sequence[sequence.size()-25]);
		sequence.push_back(num);
		preamble.insert(num);
	}
	cout << "This is the first num that doesn't meet XMAS requirement: " << num << endl;
	*/
	input_file.close();
	return 0;
}
