#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/* Day 8: Handheld Halting
 * Part 1:
 * Problem: Given boot code with each line showing an instruction, 
 * determine the accumulator count right before the loop.
 *
 * Part 2:
 * Problem: A single instruction is corrupted (a jmp to nop, or nop to jmp).
 * Fix that, and output the value of the accumulator once the program terminates.
*/

int accumulator = 0;


struct Command{
	string op;
	int quantity;
	bool visited;
};
//Part 1
void RunLine(vector<Command> &boot_code, int &ptr){
	boot_code[ptr].visited = true;
	string op = boot_code[ptr].op;	
	int quantity = boot_code[ptr].quantity;
	if(op == "acc"){
		accumulator += quantity;
		ptr++;
	}
	else if(op == "jmp"){
		ptr += quantity;
	}
	else{
		ptr++;
	}
}

void Backtracking(vector<Command> boot_code, int ptr, bool &found, bool &changed){
	if(ptr > boot_code.size() || ptr < 0) return;
	while(!boot_code[ptr].visited && ptr < boot_code.size()){
		if(!changed && boot_code[ptr].op != "acc"){
			boot_code[ptr].op = boot_code[ptr].op == "jmp" ? "nop" : "jmp";
			changed = true;
			int temp_accumulator = accumulator;
			Backtracking(boot_code, ptr, found, changed);
			if(found) return;
			boot_code[ptr].op = boot_code[ptr].op == "jmp" ? "nop" : "jmp";
			accumulator = temp_accumulator;
			changed = false;
			RunLine(boot_code,ptr);
		}
		else{
			RunLine(boot_code,ptr);
		}
	}
	found = ptr == boot_code.size();
}

int main(){
	ifstream input_file("day8.txt");
	string instruction;
	vector<Command> boot_code;
	while(getline(input_file,instruction)){
		Command cmd;
		stringstream ss(instruction);
		string str_qty;
		ss >> cmd.op >> str_qty;
		cmd.quantity = stoi(str_qty);
		cmd.visited = false;
		boot_code.push_back(cmd);
	}
	int ptr = 0;
	bool found = false, changed = false;
	Backtracking(boot_code, ptr, found, changed);
	/*
	while(!boot_code[ptr].visited){
		RunLine(boot_code,ptr);
	}
	*/
	cout << "accumulator value once finished: " << accumulator << endl;
	return 0;
}
