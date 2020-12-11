#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/*
 * Day 1: Report Repair
 *
 * Problem: Find two entries in a list that sum to 2020, then multiply those two numbers together.
 *
 * Constraints: 
 * --The largest product you can get is 1010*1010, which is a little over 1,000,000. This can fit within an int
 * --The list isn't sorted
 *
 *
*/


/*Naive Approach: Do a nested search for the two numbers. 
*This means for every element pointed to, 
*look for the other element to the right of it. 
*Time complexity: O(n^2); Space complexity: O(1)
*/
int NaiveTwoSum(const vector<int> &nums){
	for(int i = 0; i < nums.size()-1; i++){
		for(int j = i + 1; j < nums.size(); j++){
			if(nums[i] + nums[j] == 2020)
				return nums[i] * nums[j];
		}
	}
	return -1;
}

/*Hash approach: There's overlap in revisiting elements in the naive approach. 
 * To avoid this, use a hash table to keep track of numbers seen so far, 
 * then determine if the current element is the complement of a seen number w.r.t. 2020
 * Time complexity: O(n); Space complexity: O(n)
*/

int HashTwoSum(const vector<int> &nums){
	unordered_set<int> seen; //the numbers seen from the list so far
	for(const int &num: nums){
		if(seen.find(2020 - num) != seen.end()){
			return num * (2020-num);
		}
		seen.insert(num);
	}
	return -1;
}


int main(){
	ifstream input_file("day1.txt");
	string num_str;
	vector<int> nums;
	while(input_file >> num_str) nums.push_back(stoi(num_str));
	cout << "Product of two numbers (using naive method): " << NaiveTwoSum(nums) << endl;
	cout << "Product of two numbers (using hash method): " << HashTwoSum(nums) << endl;
	return 0;
}
