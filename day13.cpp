#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <signal.h>

using namespace std;

/* Day 13: Shuttle Search
 * Part 1:
 * Problem: Given a start time and a list of buses,
 * find the bus that arrives earliest on or after this start time.
 *
 * Part 2:
 * Problem: Using the same list of buses,
 * determine the earliest time where these buses arrive
 * in the order they appear in the list.
 *
 * Observation: the key here is understanding the positions of the buses relative to each other.
 * If you can meet the criteria for two buses, it makes sense that you want to preserve the
 * distance they have with each other by multiplying the two bus ids together to get the jump distance.
 * 	--The intuition for multiplying can be seen if you want to reach an intersection of points
 * 	for two numbers, let's say 5 and 7. For 5 and 7 to meet, they would have to multiply by 35 and jump to that point. 5 and 7 first meet at 0, then at 35, then at 70.
 * 	--Likewise, if you have a bus at 1, and another bus at 8, and you want the distance between
 * 	them to be preserved, you multiply the two bus speeds together and jump that distance.
*/

struct BusInfo{
	int pos;
	int id;
	BusInfo(int p, int i){
		pos = p;
		id = i;
	};
};

int Earliest1(const vector<BusInfo> &buses, const int &start_time){
	int end_time = start_time;
	bool found = false;
	int earliest_bus;
	while(!found){
		for(const auto &bus : buses){
			if(end_time % bus.id == 0){
				found = true;
				earliest_bus = bus.id;
				break;
			}
		}
		end_time += !found;
	}
	cout << "The start time is: " << start_time << endl;
	cout << "The end time is: " << end_time << endl;
	cout << "The earliest bus is: " << earliest_bus << endl;
	return (end_time - start_time) * earliest_bus;
}


unsigned long long Earliest2(vector<BusInfo> &buses){
	unsigned long long jump = buses[0].id;
	bool found = false;
	unsigned long timestamp = 0;
	unsigned long long old_time = 0, new_time = 0;
	while(!found){
		found = true;
		jump = buses[0].id;
		for(int i = 1; i < buses.size(); i++){
			if(((timestamp + buses[i].pos) % buses[i].id) != 0){
				found = false;
				break;
			}
			jump *= buses[i].id;
		}
		timestamp += found ? 0 : jump;
	}
	return timestamp;
}

int main(){
	ifstream input_file("day13.txt");
	string start_str;
	input_file >> start_str;
	int start_time = stoi(start_str);

	string id;
	vector<BusInfo> buses;
	int i = 0;
	while(getline(input_file,id,',')){
		if(id != "x"){
			buses.emplace_back(i,stoi(id));
		}
		i++;
	}
	input_file.close();
	for(auto bus: buses){
		cout << bus.pos << ": " << bus.id << endl;
	}
	//cout << "The answer is: " << Earliest1(buses, start_time) << endl;
	cout << "The answer is: " << Earliest2(buses) << endl;
	return 0;
}
