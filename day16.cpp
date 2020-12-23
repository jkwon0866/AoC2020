#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* Day 16: Ticket Translation
 * Part 1:
 * Problem: Given a list of valid number ranges and a list of numbers to check,
 * return the sum of the invalid numbers.
 *
 * Observation: Two approaches came up in my mind.
 * 	--I could store the intervals of valid ranges in a vector,
 * 	sort this and merge overlaps,
 * 	then apply binary search to each number in the list for validation.
 * 	The benefit is reduced space requirements, since you're storing
 * 	intervals, rather than the explicit numbers in between
 * 	--Or, I could store the individual state 
 * 	of each number in the ranges into a vector.
 * 	This has the benefit of reducing time complexity
 * 	per number validation (O(1) vs. O(log(k)),
 * 	where k is size of intervals vector.
 * Since the highest value among all ranges doesn't go past 1000
 * and the number of numbers to validate is larger and can change to be higher,
 * I deem the second approach to be best for this scenario.
 * 
 * Part 2:
 * Problem: Determine the fields for your numbers, 
 * and multiply the values in your ticket
 * that correspond to "departure" fields.
 *
*/

ifstream input_file;

struct Interval{
	int start;
	int end;
	Interval(int s, int e){
		start = s;
		end = e;
	};
};

struct Field{
	string key;
	vector<Interval> intervals;
};

void PopulateValidNumbers1(vector<bool> &valid_numbers){
	string line;
	while(getline(input_file,line) && !line.empty()){
		stringstream ss(line);
		string range;
		while(ss >> range && range.back() != ':');
		while(ss >> range){
			if(range != "or"){
				int delim_pos = range.find('-');
				int low = stoi(range.substr(0,delim_pos));
				int hi = stoi(range.substr(delim_pos + 1));
				//cout << low << ", " << hi << endl;
				if(hi >= valid_numbers.size()) valid_numbers.resize(hi+1,false);
				fill(valid_numbers.begin()+low,valid_numbers.begin()+hi+1,true);
			}
		}
	}
}

void PopulateValidNumbers2(vector<Field> &valid_numbers){
	string line;
	while(getline(input_file,line) && !line.empty()){
		stringstream ss(line);
		string key, range;
		Field field;
		while(ss >> range){
			key += range;
			if(range.back() == ':') break;	
		}
		field.key = key;
		while(ss >> range){
			if(range != "or"){
				int delim_pos = range.find('-');
				int low = stoi(range.substr(0,delim_pos));
				int hi = stoi(range.substr(delim_pos + 1));
				field.intervals.emplace_back(low,hi);
			}
		}
		valid_numbers.push_back(field);
	}
}


void ProcessYourTicket(vector<int> &your_ticket){
	string line;
	getline(input_file,line);
	getline(input_file,line);

	stringstream ss(line);
	string num_str;
	while(getline(ss, num_str,','))
		your_ticket.push_back(stoi(num_str));
	//for(int num : your_ticket)
		//cout << num << ", ";
	//cout << endl;
	while(getline(input_file,line) && !line.empty());
}

int ProcessOtherTickets1(const vector<Field> &fields){
	int sum = 0;
	/*
	 * TODO: change valid_numbers to fields
	string line;
	getline(input_file,line);
	cout << line << endl;
	cout << fields.size() << endl;
	while(getline(input_file,line)){
		stringstream ss(line);
		string num_str;
		while(getline(ss,num_str,',')){
			int num = stoi(num_str);
			//determine if valid or not
			sum += (num >= valid_numbers.size() || !valid_numbers[num]) ? num : 0;
		}
	}
	*/
	return sum;
}


bool Valid(int num, const Field &field){
	for(auto interval: field.intervals){
		if(num >= interval.start && num <= interval.end) return true;	
	}
	return false;
}

void Invalidate(int row, int skip_col, vector<vector<bool>> &possible_fields){
	for(int col = 0; col < possible_fields.size(); col++){
		if(col == skip_col) continue;
		possible_fields[row][col] = false;	
	}
}

/* possible_fields:
 * row - the position on the listed fields
 * col - the position on the ticket
*/
unsigned long ProcessOtherTickets2(const vector<Field> &fields, const vector<int> &your_ticket){
	vector<vector<bool>> possible_fields(fields.size(), vector<bool>(fields.size(), true));
	int sum = 0;
	string line;
	getline(input_file,line);
	while(getline(input_file,line)){
		int col = 0;
		stringstream ss(line);
		string num_str;
		//check each number that appears on a ticket
		while(getline(ss,num_str,',')){
			int num = stoi(num_str);
			bool valid = false;
			vector<bool> temp;
			for(int row = 0; row < fields.size(); row++)
				temp.push_back(possible_fields[row][col]);
			for(int row = 0; row < fields.size(); row++){
				//compare that number with all the intervals of the fields
				possible_fields[row][col] = possible_fields[row][col] && Valid(num,fields[row]);
				valid = valid || possible_fields[row][col];
			}
			if(!valid){
				for(int row = 0; row < fields.size(); row++)
					possible_fields[row][col] = temp[row];
				col++;
				break;
			}
			col++;
		}
	}
	/*
	for(int i = 0; i < fields.size(); i++){
		for(int j = 0; j < fields.size(); j++){
			cout << possible_fields[i][j] << ", ";
		}
		cout << endl;
	}
	*/

	//de-duplicate/isolate the valid positions
	unsigned long product = 1;
	vector<bool> used(fields.size(), false);
	int used_count = 0;
	int col = 0;
	while(used_count < used.size()){
		vector<int> valid_positions;
		/*
		cout << fields[row].key << ": " << endl;
		for(auto interval : fields[row].intervals){
			cout << "(" << interval.start << ", " << interval.end << ")" << "; ";
		}
		cout << endl;
		*/
		//Get the valid_positions for this ticket position (col)
		for(int row = 0; row < fields.size(); row++){
			if(possible_fields[row][col]) valid_positions.push_back(row);
		}
		//skip this column if can't determine a singular valid position
		if(valid_positions.size() > 1){
			col++;
			continue;
		}
		int valid_row = valid_positions[0];
		//invalidate all other rows for that column
		Invalidate(valid_row, col, possible_fields);
		if(fields[valid_row].key.find("departure") != string::npos && !used[valid_row])
			product *= your_ticket[col];
		if(!used[valid_row]){
			used[valid_row] = true; used_count++;
			col = 0;
		}
		else{
			col++;
		}
	}
	/*
	for(int i = 0; i < fields.size(); i++){
		for(int j = 0; j < fields.size(); j++){
			cout << possible_fields[i][j] << ", ";
		}
		cout << endl;
	}
	*/
	return product;
}

int main(){
	input_file.open("day16.txt");
	//the fields as they appear in the puzzle input
	vector<Field> fields;
	vector<int> your_ticket;
	PopulateValidNumbers2(fields);
	ProcessYourTicket(your_ticket);
	cout << ProcessOtherTickets2(fields, your_ticket) << endl;
	input_file.close();
	return 0;
}
