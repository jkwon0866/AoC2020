#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Day 5: Binary Boarding
 * Part 1:
 * Problem: A boarding pass is defined as 7 characters of F or B, followed by 3 characters of L or R.
 * The group of seats are binary partitioned to the lower and upper half, respectively.
 * The seat id is defined as row * 8 + col
 * Given all boarding passes, return the highest seat id found
 *
 * Part 2:
 * Problem: The only seats that should be missing are yours and anybody from the front-most row (0-7)
 * and back-most row (1016-1023). Your seat is not in the front-most or back-most row.
 * Also, the ids +1 and -1 from yours will be in your list. 
 * Return your seat id
*/

int SeatId(const string &bpass){
	int row, col;
	int low = 0, hi = 127; int mid;
	for(int i = 0; i < 7; i++){
		mid = (low + hi)/2;
		if(bpass[i] == 'F')
			hi = mid;
		else
			low = mid + 1;
	}
	row = low;
	low = 0; hi = 7;
	for(int i = 7; i < 10; i++){
		mid = (low + hi)/2;
		if(bpass[i] == 'L')
			hi = mid;
		else
			low = mid + 1;
	}
	col = low;
	return row * 8 + col;
}	

int main(){
	ifstream input_file("day5.txt");
	string bpass;
	vector<bool> available(1024,false);
	//int max_seat_id = 0;
	while(input_file >> bpass){
		available[SeatId(bpass)] = true;
		//max_seat_id = max(max_seat_id, SeatId(bpass));
	}
	//cout << "This is the highest seat id: " << max_seat_id << endl;
	input_file.close();
	for(int i = 8; i < 1016; i++){
		if(!available[i] && available[i-1] && available[i+1])
			cout << "My seat id is: " << i << endl;
	}
	return 0;
}
