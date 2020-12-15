#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Day 11: Seating System
 * Part 1:
 * Problem: Run a simulation of the seating layout changes until stablized,
 * then output the number of occupied seats.
 * --An empty seat becomes occupied if the surrounding seats are all empty.
 * --An occupied seat becomes empty if there are 4 or more seats that are occupied around it.
 *
 * Part 2:
 * Problem: Run a simulation again, but this time two modifications to the rules:
 * --The number of surrounding seats are based on what's first viewed in all directions.
 * --An occupied seat becomes empty if there are 5 (not 4) or more seats occupied around it.
*/

bool WithinBounds(const vector<string> &layout, int row, int col){
	//cout << "entered WithinBounds" << endl;
	return row >= 0 && row < layout.size() && col >= 0 && col < layout[0].size();
}


//Part 1's version of NumSurrounded
int NumSurrounded1(const vector<string> &layout, int row, int col){
	//cout << "entered NumSurrounded" << endl;
	int count = 0;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if(WithinBounds(layout, row + i, col + j) && (i != 0 || j != 0))
				count += layout[row+i][col+j] == '#';
		}
	}
	return count;
}

//Part 2's version of NumSurrounded
int NumSurrounded2(const vector<string> &layout, int row, int col){
	//cout << "entered NumSurrounded" << endl;
	int count = 0;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			if(i != 0 || j != 0){
				int k = 1;
				bool seen = false;
				while(!seen && WithinBounds(layout, row + i*k, col + j*k)){
					switch(layout[row + i*k][col + j*k]){
						case 'L':
							seen = true;
							break;
						case '#':
							seen = true;
							count++;
							break;
						default:
							break;
					}
					k++;
				}
			}
		}
	}
	return count;
}

bool WillChange(const vector<string> &layout, int row, int col){
	//cout << "entered WillChange" << endl;
	switch(layout[row][col]){
		case 'L':
			return NumSurrounded2(layout, row, col) == 0;
		case '#':
			//Commented is for part 1
			return NumSurrounded2(layout, row, col) >= 5;//4;
		default:
			return false;
	}
}

void ChangeLayout(vector<string> &layout, const vector<vector<bool>> &will_change, bool &changed){
	//cout << "entered ChangeLayout" << endl;
	int rows = layout.size(), cols = layout[0].size();
	for(int row = 0; row < rows; row++){
		for(int col = 0; col < cols; col++){
			if(will_change[row][col]){
				layout[row][col] = layout[row][col] == 'L' ? '#' : 'L';
				changed = true;
			}
		}	
	}	
}

void Simulate(vector<string> &layout){
	//cout << "entered Simulate" << endl;
	bool changed = false;
	int rows = layout.size();
	int cols = layout[0].size();
	do{
		changed = false;
		vector<vector<bool>> will_change(rows, vector<bool>(cols,false));
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++)
				will_change[i][j] = WillChange(layout,i,j);
		}
		ChangeLayout(layout,will_change,changed);
	}while(changed);
}

int NumOccupied(const vector<string> &layout){
	//cout << "entered NumOccupied" << endl;
	int count = 0;
	int rows = layout.size(), cols = layout[0].size();
	//cout << "rows: " << rows << endl;
	//cout << "cols: " << cols << endl;
	//cout << "product: " << rows * cols << endl;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			//cout << layout[i][j];
			count += layout[i][j] == '#';
		}
		//cout << endl;
	}
	return count;
}

int main(){
	ifstream input_file("day11.txt");
	string row;
	vector<string> layout;
	while(getline(input_file,row)){
		layout.push_back(row);
	}
	input_file.close();
	Simulate(layout);
	cout << "Number of occupied seats: " << NumOccupied(layout) << endl; 
	return 0;
}
