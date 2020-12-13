#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

/* Day 6:
 * Part 1:
 * Problem: For each group, the unique yes answers for questions a-z are collected.
 * Return the sum of these combined counts for all groups.
 *
 * Part 2:
 * Problem: Count the number of questions to which everyone (not just anyone) in a group said yes.
*/

int AllYes(unordered_map<char,int> &group_answers, int &group_count){
	int count = 0;
	for(auto it: group_answers){
		count += it.second == group_count;
	}
	return count;
}

int main(){
	ifstream input_file("day6.txt");
	string yes_answers;
	int total = 0;
	unordered_map<char,int> group_answers;
	int group_count = 0;
	while(getline(input_file,yes_answers)){
		if(yes_answers.empty()){
			//cout << "at empty line" << endl;
			//total += group_answers.size();
			total += AllYes(group_answers,group_count);
			group_answers.clear();
			group_count = 0;
			continue;
		}
		for(char c: yes_answers)
			group_answers[c]++;
		group_count++;
	}
	total += AllYes(group_answers,group_count);
	cout << "This is the total yes answers: " << total << endl;
	return 0;
}
