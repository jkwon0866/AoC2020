#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/*
 * Day 1: Report Repair
 *
 * Part 1:
 * Problem: Find two entries in a list that sum to 2020, then multiply those two numbers together.
 *
 * Constraints: 
 * --The largest product you can get is 1010*1010, which is a little over 1,000,000. This can fit within an int.
 * --The list isn't sorted.
 *
 * Part 2:
 * Problem: Find three numbers that meet the same criteria.
 * Constraints:
 * --The largest product this time is 673*673*674, which is a little over 300,000,000. This still fits within an int.
 *  --The list isn't sorted.
*/



//---------------------Part 1-----------------------//
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

int HashTwoSum(const vector<int> &nums, int target){
	unordered_set<int> seen; //the numbers seen from the list so far
	for(const int &num: nums){
		if(seen.find(target - num) != seen.end()){
			return num * (target-num);
		}
		seen.insert(num);
	}
	return -1;
}

//--------------------End of Part 1------------------//

//--------------------Part 2-------------------------//
/* Naive Approach: Do a triple nested search for all possible combinations of numbers,  
 * then return the one that sums to 2020.
 * Time Complexity: O(n^3); Space Complexity: O(1)
*/
int NaiveThreeSum(const vector<int> &nums){
	for(int i = 0; i < nums.size()-2; i++){
		for(int j = i + 1; j < nums.size()-1; j++){
			for(int k = j + 1; k < nums.size(); k++)
				if(nums[i] + nums[j] + nums[k] == 2020)
					return nums[i] * nums[j] * nums[k];
		}
	}
	return -1;
}

/* Naive/Hash Hybrid: Combine a linear search with the Hash search
 * Time complexity: O(n^2); Space Complexity: O(n)
 *
*/
int HybridThreeSum(const vector<int> &nums){
	for(int i = 0; i < nums.size()-1; i++){
		int target = 2020 - nums[i];
		unordered_set<int> seen;
		for(int j = i + 1; j < nums.size(); j++){
			if(seen.find(target - nums[j]) != seen.end())
				return nums[i] * nums[j] * (target - nums[j]);
			seen.insert(nums[j]);
		}
	}
	cout << "couldn't find it" << endl;
	return -1;
}

//---------------------End of Part 2---------------------//

int main(){
	ifstream input_file("day1.txt");
	string num_str;
	vector<int> nums;
	while(input_file >> num_str) nums.push_back(stoi(num_str));
	//for part 1
	cout << "Product of two numbers (using naive method): " << NaiveTwoSum(nums) << endl;
	cout << "Product of two numbers (using hash method): " << HashTwoSum(nums,2020) << endl;
	//for part 2
	cout << "Product of three numbers (using naive method): " << NaiveThreeSum(nums) << endl;
	cout << "Product of three numbers (using hybrid method): " << HybridThreeSum(nums) << endl;
	return 0;
}
