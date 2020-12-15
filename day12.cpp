#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Day 12: Rain Risk
 * Part 1:
 * Problem: Given a list of actions for a ship to take, determine the Manhattan distance of the ship.
 * All of the actions are interpreted to be done on the ship directly.
 *
 * Assumption: Degrees will be in multiples of 90 to simplify calculation of forward movement.
 *
 * Part 2:
 * Problem: Directional movements and rotations will be done on a waypoint.
 * Only the forward action moves the ship itself.
 * Given the actual actions to take, determine the Manhattan distance of the ship this time.
 *
*/



struct Ship{
	int horiz;
	int vert;
	int direction;
	vector<int> directions;
	Ship(){
		horiz = 0; vert = 0; direction = 0;
		directions.resize(4,0);
	};
};

struct WayPoint{
	vector<int> directions;
	WayPoint(){
		directions.resize(4,0);
		directions[0] = 10;
		directions[3] = 1;
	};
};

//Part 1
void TakeAction1(const string &action, Ship &ship){
	int quantity = stoi(action.substr(1));
	switch(action.front()){
		case 'N':
			ship.vert += quantity;
			break;
		case 'S':
			ship.vert -= quantity;
			break;
		case 'W':
			ship.horiz -= quantity;
			break;
		case 'E':
			ship.horiz += quantity;
			break;
		case 'L':
			ship.direction = (ship.direction + quantity/30)%4;
			break;
		case 'R':
			ship.direction = (ship.direction + quantity/90)%4;
			break;
		case 'F':
			ship.directions[ship.direction] += quantity;
			break;
		default:
			break;
	}
}

void Rotate(WayPoint &waypoint, const int &degrees, bool clockwise){
	vector<int> directions(4,0);
	for(int i = 0; i < 4; i++){
		directions[(i+ degrees/(clockwise ? 90 : 30))%4] = waypoint.directions[i];
	}
	waypoint.directions = directions;
}

void Relocate(Ship &ship, const WayPoint &waypoint, const int &multiplier){
	for(int i = 0; i < 4; i++){
		switch(i){
			case 0://East
				ship.horiz += waypoint.directions[0] * multiplier;
				break;
			case 1://South
				ship.vert -= waypoint.directions[1] * multiplier;
				break;
			case 2://West
				ship.horiz -= waypoint.directions[2] * multiplier;
				break;
			case 3://North
				ship.vert += waypoint.directions[3] * multiplier;
				break;
			default:
				break;
		}
	}
}

void TakeAction2(const string &action, Ship &ship, WayPoint &waypoint){
	int quantity = stoi(action.substr(1));
	switch(action.front()){
		case 'N':
			waypoint.directions[3] += quantity;
			break;
		case 'S':
			waypoint.directions[1] += quantity;
			break;
		case 'W':
			waypoint.directions[2] += quantity;
			break;
		case 'E':
			waypoint.directions[0] += quantity;
			break;
		case 'L':
			Rotate(waypoint,quantity,false);
			break;
		case 'R':
			Rotate(waypoint,quantity,true);
			break;
		case 'F':
			Relocate(ship,waypoint,quantity);
			break;
		default:
			break;
	}
}

int main(){
	ifstream input_file("day12.txt");
	string action;
	Ship ship;
	WayPoint waypoint;
	while(input_file >> action)
		TakeAction2(action,ship,waypoint);
	input_file.close();

	/*Part 1:
	while(input_file >> action)
		TakeAction1(action,ship);
	input_file.close();
	ship.horiz += (ship.directions[0] - ship.directions[2]);
	ship.vert += (ship.directions[3] - ship.directions[1]);
	*/
	cout << "This is the horiz: " << ship.horiz << endl;
	cout << "This is the vert: " << ship.vert << endl;
	cout << "This is the Manhattan distance: " << abs(ship.horiz) + abs(ship.vert) << endl;
	return 0;
}
