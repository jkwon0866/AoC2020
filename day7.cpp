#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/* Day 7: Handy Haversacks
 * Part 1:
 * Problem: Each bag can contain multiple quantities of other bags.
 * Return the number of outer bag colors that can hold a shiny gold bag.
 *
 * Assumption: There isn't a cycle in the bags contained. 
 * For example, a white bag contained in a yellow bag can't itself eventually contain a white bag.
 *
 * Observations: --a specific-colored bag can be contained in many other bags, so rather than
 * a simple tree, it's more accurate to say this is a directed, acyclic graph.
 * The key to solving part 1 is defining the relationship of the inner bag to the outer bags
 * that may contain it. If the outer bag points to the inner bag, there's no way 
 * for the inner bag to know who is pointing to it. So, we have to reverse it for Part 1.
 *
 * Part 2:
 * Problem: Find the total number of bags that will be in a shiny gold bag.
 *
*/

typedef unordered_map<string,vector<pair<string,int>>> OuterMapping;
typedef OuterMapping InnerMapping;

//Part 1: OuterMapping key is the inner bag color, the values are the possible outer bag colors
void AddInnerBag(const string &bag_rule, OuterMapping &child_parents){
	stringstream ss(bag_rule);
	string key_word, key_color;
	while((ss >> key_word) && key_word != "bags"){
		key_color += key_word;
	}
	ss >> key_word;
	string value_word;
	while(ss >> value_word){
		if(value_word == "no") return;
		int quantity = stoi(value_word);
		string value_color;
		while((ss >> value_word) && value_word.substr(0,min((int)value_word.size(),3)) != "bag"){
			value_color += value_word;
		}
		child_parents[value_color].emplace_back(key_color,1);
	}
}
//Part 1
void DFS1(string current_bag, OuterMapping &child_parents, int &bag_count, unordered_set<string> &seen){
	seen.insert(current_bag);
	auto &parents = child_parents[current_bag];
	for(auto &parent: parents){
		if(seen.find(parent.first) == seen.end()){
			bag_count++;
			DFS1(parent.first, child_parents, bag_count, seen);
		}
	}
}

//Part 2: InnerMapping key is the outer bag color, the values are the inner bag colors
void AddOuterBag(const string &bag_rule, InnerMapping &children_map){
	stringstream ss(bag_rule);
	string key_word, key_color;
	while((ss >> key_word) && key_word != "bags"){
		key_color += key_word;
	}
	ss >> key_word;
	string value_word;
	vector<pair<string,int>> &outer_bags = children_map[key_color];
	while(ss >> value_word){
		if(value_word == "no") return;
		int quantity = stoi(value_word);
		string value_color;
		while((ss >> value_word) && value_word.substr(0,min((int)value_word.size(),3)) != "bag"){
			value_color += value_word;
		}
		outer_bags.emplace_back(value_color,quantity);
	}
}

//Part 1
int DFS2(string current_bag, InnerMapping &children_map){
	auto &children = children_map[current_bag];
	int count = 0;
	for(auto &child: children){
		count += child.second * DFS2(child.first, children_map);
	}
	return count + 1;
}

int main(){
	ifstream input_file("day7.txt");
	string bag_rule;
	OuterMapping child_parents;
	while(getline(input_file,bag_rule)){
		AddOuterBag(bag_rule,child_parents);
	}
	input_file.close();
	/*ofstream output_file("day7_output.txt");
	for(auto it: child_parents){
		output_file << it.first << ": ";
		auto &parents = it.second;
		for(auto it2: parents){
			output_file << it2.first << ", " << it2.second << "; ";
		}
		output_file << endl;
	}
	output_file.close();
	*/
	//int bag_count = 0;
	//unordered_set<string> seen;
	cout << "number of bags (including outer): " << DFS2("shinygold",child_parents) << endl;
	//cout << "This is the number of outer bags: " << bag_count;
	return 0;
}

