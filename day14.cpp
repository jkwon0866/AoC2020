#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

/* Day 14: Docking Data
 * Part 1:
 * Problem: The mask is applied to the value. Get the total sum of all values in memory.
 *
 * Part 2:
 * Problem: The mask is applied to the keys. Get the total sum of all values in memory.
 *
*/

typedef unsigned long long ull;

unordered_map<ull,ull> memory;
void UpdateMasks(ull &zero_mask, ull &one_mask, 
		vector<ull> &x_mask, string &mask){
	zero_mask = 0x0000000FFFFFFFFF;
       	one_mask = 0;
	x_mask.clear();
	ull bit = 1;
	for(int i = 0; i < mask.size(); i++, bit *= 2){
		switch(mask[mask.size()-1-i]){
			case '0':
				zero_mask &= (0x0000000FFFFFFFFF & ~bit);
				break;
			case '1':
				one_mask |= bit;
				break;
			case 'X':
				x_mask.push_back(bit);
				break;
			default:
				break;
		}
	}
}

void UpdateAndAddValue(ull &key, ull &value, const ull &zero_mask, const ull &one_mask){
	value |= one_mask;
	value &= zero_mask;
	memory[key] = value;
}

void AddKeys(int start, ull &key, ull &value, const vector<ull> &x_mask){
	memory[key] = value;
	for(int i = start; i < x_mask.size(); i++){
		key ^= x_mask[i];
		AddKeys(i+1, key, value, x_mask);
		key ^= x_mask[i];
	}
}

void UpdateAndAddKeys(ull &key, ull &value, const ull &one_mask, const vector<ull> &x_mask){
	key |= one_mask;
	AddKeys(0, key, value, x_mask);
}

int main(){
	ifstream input_file("day14.txt");
	ull zero_mask, one_mask;
	vector<ull> x_mask;
	string line, word;
	while(getline(input_file,line)){
		stringstream ss(line);
		if(ss >> word && word == "mask"){
			ss >> word >> word;
			UpdateMasks(zero_mask,one_mask,x_mask,word);
		}
		else{
			//extract key and value from ss line
			ull key = stoi(word.substr(4,word.size()-5));
			ss >> word >> word;
			ull value = stoi(word);
			//cout << key << ": " << value << endl;
			//Part 1
			//UpdateAndAddValue(key,value,zero_mask,one_mask);
			UpdateAndAddKeys(key,value,one_mask,x_mask);
		}
	}
	ull sum = 0;
	for(auto it: memory){
		sum += it.second;
	}
	cout << "Total sum: " << sum << endl;

	return 0;
}
