#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Day 3: Toboggan Trajectory
 * Part 1:
 * Problem: Count the number of trees encountered when starting from top-left and moving right 3, down 1.
 *
 * Constraints: the layout of the trees repeats itself to the right.
 * In other words, the same map can be reused when moving to the right.
 * Part 2:
 * Problem: Same problem as before, but applied to: right 1, down 1; right 3, down 1;
 * right 5, down 1; right 7, down 1; right 1, down 2
*/


int NumTrees(const vector<string> &layout, const int &right, const int &down){
	int column_pos = 0;
	int column_size = layout[0].size();
	int trees = 0;
	for(int i = 0; i < layout.size(); i+= down){
		trees += layout[i][column_pos] == '#';
		column_pos = (column_pos + right) % column_size;
	}
	return trees;
}


int main(){
	vector<string> layout;
	ifstream input_file("day3.txt");
	string line;
	while(input_file >> line) layout.push_back(line);
	input_file.close();
	//Note: Multiplying multiple NumTrees calls together gives the incorrect answer.
	unsigned long long product = 1;//NumTrees(layout,1,1) * NumTrees(layout,3,1) * NumTrees(layout,5,1) * NumTrees(layout,7,1) * NumTrees(layout,1,2);
	product *= NumTrees(layout,1,1);
	product *= NumTrees(layout,3,1);
	product *= NumTrees(layout,5,1);
	product *= NumTrees(layout,7,1);
	product *= NumTrees(layout,1,2);
	cout << "The product of all trees encountered is: " << product << endl;
	return 0;
}
