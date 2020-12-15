#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <climits>

using namespace std;

/* Day 10: Adapter Array
 * Part 1:
 * Problem: To charge your device, you need to connect from the charging outlet (0 jolt output) 
 * through a chain of adapters (input must be 1-3 lower than its output jolt rating).
 * Your device's internal adapter rating is 3 higher than the highest adapter.
 * Output the product of 1 intervals and 3 intervals.
 *
 * Constraints: --Every adapter must be used.
 *
 * Observations: --Since the input to an adapter must be 1-3 less than its output, the sequence of adapters used is strictly increasing. 
 * Iow, there shouldn't any repeated numbers.
 * --There are three choices to be made for the next adapter to select: 
 *  always start from 1 and move up. Why? Let's suppose you moved up by 2 instead of 1. 
 *  If an adapter existed at 1 interal, you won't be able to go back to it,
 *  and you don't meet the problem requirement of using all adapters.
 *
 * Part 2:
 * Problem: This time, count all the distinct ways you can rearrange the adapters to connect the charging outlet to your device.
 * You don't need to use all adapters for an arrangement.
 *
 * Observation: --This problem can be solved with dynamic programming. Each adapter has a constant total number of ways to get there,
 * defined by the recurrence relation: A[i] = A[i-3] + A[i-2] + A[i-1].
 * To solve this in O(n) time, seed the A[0],A[1],A[2],A[3] values,
 * then incrementally evaluate the next element with the recurrence relation.
 * Note that if an adapter doesn't exist at a position, that element should be 0.
*/

//Part 1
unsigned long IntervalCounts(unordered_set<int> &unused){
	vector<int> intervals(4,0);
	int jolt = 0;
	while(!unused.empty()){
		for(int i = 1; i <= 3; i++){
			if(unused.find(jolt+i) != unused.end()){
				unused.erase(jolt+i);
				jolt += i;
				intervals[i]++;
				break;
			}
		}
	}
	intervals[3]++;
	cout << "interval 1 count: " << intervals[1] << endl;
	cout << "interval 3 count: " << intervals[3] << endl;
	return intervals[1] * intervals[3];
}

//Part 2
unsigned long NumArrangements(unordered_set<int> &unused, int max_rating){
	//cout << "Max rating: " << max_rating << endl;
	vector<unsigned long> dp(1 + max_rating + 3,0);
	//Seed dp[0]->dp[2]
	dp[0] = 1;
	dp[1] = unused.find(1) != unused.end();
	dp[2] = unused.find(2) != unused.end() ? 2 : 0;
	for(int i = 3; i <= max_rating+3; i++){
		dp[i] = unused.find(i) != unused.end() ? dp[i-1] + dp[i-2] + dp[i-3] : 0;
		//cout << i << ": " << dp[i] << endl;
	}
	return dp.back();
}

int main(){
	ifstream input_file("day10.txt");
	string rating;
	unordered_set<int> unused;
	int max_rating = INT_MIN;
	while(input_file >> rating){
		unused.insert(stoi(rating));
		max_rating = max(max_rating, stoi(rating));
	}
	unused.insert(max_rating+3);
	input_file.close();
	cout << "This is total distinct arrangements: " << NumArrangements(unused,max_rating) << endl;
	//cout << "Product is: " << IntervalCounts(unused) << endl;
	return 0;
}
