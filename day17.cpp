#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Cube{
	bool will_change;
	bool active;
	Cube(bool w, bool a){
		will_change = w;
		active = a;
	};
};

typedef vector<Cube> OneD;
typedef vector<OneD> TwoD;
typedef vector<TwoD> ThreeD;
typedef vector<ThreeD> FourD;


bool WithinBounds(int x, int y, int z, ThreeD &dimension){
	return z >= 0 && z < dimension.size()
		&& y >= 0 && y < dimension[0].size() 
		&& x >= 0 && x < dimension[0][0].size();
}

bool WithinBounds(int x, int y, int z, int w, FourD &dimension){
	return w >= 0 && w < dimension.size()
		&& z >= 0 && z < dimension[0].size()
		&& y >= 0 && y < dimension[0][0].size() 
		&& x >= 0 && x < dimension[0][0][0].size();
}

int NumActive(int x, int y, int z, ThreeD &dimension){
	int count = 0;
	for(int x_off = -1; x_off <= 1; x_off++){
		for(int y_off = -1; y_off <= 1; y_off++){
			for(int z_off = -1; z_off <= 1; z_off++){
				if(WithinBounds(x + x_off, y + y_off, z + z_off,dimension) && x_off || y_off || z_off)
					count += dimension[z+z_off][y+y_off][x+x_off].active;
			}
		}
	}
	return count;
}
int NumActive(int x, int y, int z, int w, FourD &dimension){
	int count = 0;
	for(int x_off = -1; x_off <= 1; x_off++){
		for(int y_off = -1; y_off <= 1; y_off++){
			for(int z_off = -1; z_off <= 1; z_off++){
				for(int w_off = -1; w_off <= 1; w_off++){
					if(WithinBounds(x + x_off, y + y_off, z + z_off, w + w_off, dimension) && (x_off || y_off || z_off || w_off))
						count += dimension[w+w_off][z+z_off][y+y_off][x+x_off].active;
				}
			}
		}
	}
	return count;
}

void WillChange(ThreeD &dimension){
	for(int z = 0; z < dimension.size(); z++){
		for(int y = 0; y < dimension[0].size(); y++){
			for(int x = 0; x < dimension[0][0].size(); x++){
				int num_active = NumActive(x,y,z,dimension);
				if(dimension[z][y][x].active){
					dimension[z][y][x].will_change = num_active < 2 || num_active > 3;
				}
				else{
					dimension[z][y][x].will_change = num_active == 3;
				}
			}
		}
	}
}

void WillChange(FourD &dimension){
	for(int w = 0; w < dimension.size(); w++){
		for(int z = 0; z < dimension[0].size(); z++){
			for(int y = 0; y < dimension[0][0].size(); y++){
				for(int x = 0; x < dimension[0][0][0].size(); x++){
					int num_active = NumActive(x,y,z,w,dimension);
					if(dimension[w][z][y][x].active){
						dimension[w][z][y][x].will_change = num_active < 2 || num_active > 3;
					}
					else{
						dimension[w][z][y][x].will_change = num_active == 3;
					}
				}
			}
		}
	}
}

void Change(ThreeD &dimension){
	for(int z = 0; z < dimension.size(); z++){
		for(int y = 0; y < dimension[0].size(); y++){
			for(int x = 0; x < dimension[0][0].size(); x++){
				dimension[z][y][x].active ^= dimension[z][y][x].will_change;
				dimension[z][y][x].will_change = false;
			}
		}
	}
}
void Change(FourD &dimension){
	for(int w = 0; w < dimension.size(); w++){
		for(int z = 0; z < dimension[0].size(); z++){
			for(int y = 0; y < dimension[0][0].size(); y++){
				for(int x = 0; x < dimension[0][0][0].size(); x++){
					dimension[w][z][y][x].active ^= dimension[w][z][y][x].will_change;
					dimension[w][z][y][x].will_change = false;
				}
			}
		}
	}
}
void Simulate(ThreeD &dimension,int cycles){
	for(int cycle = 1; cycle <= cycles; cycle++){
		WillChange(dimension);
		Change(dimension);
	}
}
void Simulate(FourD &dimension,int cycles){
	for(int cycle = 1; cycle <= cycles; cycle++){
		WillChange(dimension);
		Change(dimension);
	}
}
int Count(ThreeD &dimension){
	int count = 0;
	for(int z = 0; z < dimension.size(); z++){
		for(int y = 0; y < dimension[0].size(); y++){
			for(int x = 0; x < dimension[0][0].size(); x++){
				count += dimension[z][y][x].active;
			}
		}
	}
	return count;
}
int Count(FourD &dimension){
	int count = 0;
	for(int w = 0; w < dimension.size(); w++){
		for(int z = 0; z < dimension[0].size(); z++){
			for(int y = 0; y < dimension[0][0].size(); y++){
				for(int x = 0; x < dimension[0][0][0].size(); x++){
					count += dimension[w][z][y][x].active;
				}
			}
		}
	}
	return count;
}
void Build3D(int cycles, ThreeD &dimension){
	ifstream input_file("day17.txt");
	string line_str;
	TwoD plane;
	while(getline(input_file,line_str) && !line_str.empty()){
		OneD line(cycles,Cube(false,false));
		for(char c: line_str){
			line.emplace_back(false, c == '#');
		}
		line.insert(line.end(),cycles,Cube(false,false));
		plane.push_back(line);
	}
	input_file.close();
	plane.insert(plane.begin(),cycles,OneD(plane[0].size(),Cube(false,false)));
	plane.insert(plane.end(),cycles,OneD(plane[0].size(),Cube(false,false)));
	dimension.insert(dimension.end(),cycles,TwoD(plane.size(),OneD(plane[0].size(),Cube(false,false))));
	dimension.insert(dimension.end(),plane);
	dimension.insert(dimension.end(),cycles,TwoD(plane.size(),OneD(plane[0].size(),Cube(false,false))));
}

void Build4D(int cycles, FourD &dimensions){
	ThreeD dimension;
	Build3D(cycles, dimension);
	dimensions.insert(dimensions.end(),cycles,ThreeD(dimension.size(),TwoD(dimension[0].size(),OneD(dimension[0][0].size(),Cube(false,false)))));
	dimensions.insert(dimensions.end(),dimension);
	dimensions.insert(dimensions.end(),cycles,ThreeD(dimension.size(),TwoD(dimension[0].size(),OneD(dimension[0][0].size(),Cube(false,false)))));
}
int main(){
	FourD dimension;
	int cycles = 6;
	Build4D(cycles,dimension);
	/*
	cout << "a: " << dimension.size() << endl;
	cout << "z: " << dimension[0].size() << endl;
	cout << "y: " << dimension[0][0].size() << endl;
	cout << "x: " << dimension[0][0][0].size() << endl;
	for(int a = 0; a < dimension.size(); a++){
		cout << "a " << a << ": " << endl;
		for(int z = 0; z < dimension[0].size(); z++){
			cout << "z " << z << ": " << endl;
			for(int y = 0; y < dimension[0][0].size(); y++){
				for(int x = 0; x < dimension[0][0][0].size(); x++){
					cout << (dimension[a][z][y][x].active ? '#' : '.') << " ";
				}
				cout << endl;
			}
		}
	}
	*/
	Simulate(dimension,cycles);
	cout << Count(dimension) << endl;
	/*
	for(int a = 0; a < dimension.size(); a++){
		cout << "a " << a << ": " << endl;
		for(int z = 0; z < dimension[0].size(); z++){
			cout << "z " << z << ": " << endl;
			for(int y = 0; y < dimension[0][0].size(); y++){
				for(int x = 0; x < dimension[0][0][0].size(); x++){
					cout << (dimension[a][z][y][x].active ? '#' : '.') << " ";
				}
				cout << endl;
			}
		}
	}
	*/
	return 0;
}
