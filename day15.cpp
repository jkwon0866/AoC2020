#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


void ElfGame1(int rounds){
	unordered_map<int,pair<int,int>> round_spoken({{2,{1,-1}},{1,{2,-1}},{10,{3,-1}},{11,{4,-1}},{0,{5,-1}},{6,{6,-1}}});
	int last_spoken = 6;
	for(int round = round_spoken.size() + 1; round <= rounds; round++){
		if(round_spoken[last_spoken].second == -1){
			last_spoken = 0;
		}
		else{
			last_spoken = round_spoken[last_spoken].second - round_spoken[last_spoken].first;
		}
		//cout << last_spoken << endl;
		if(round_spoken.find(last_spoken) == round_spoken.end()){
			round_spoken[last_spoken] = {round,-1};
		}
		else if(round_spoken[last_spoken].second == -1){
			round_spoken[last_spoken].second = round;
		}
		else{
			round_spoken[last_spoken].first = round_spoken[last_spoken].second;
			round_spoken[last_spoken].second = round;
		}
	}
	cout << last_spoken << endl;
}
void ElfGame2(int rounds){
	unordered_map<int,int> round_spoken({{2,1},{1,2},{10,3},{11,4},{0,5},{6,6}});
	vector<int> dp(rounds+1,0);
	dp[1] = 2; dp[2] = 1; dp[3] = 10; dp[4] = 11; dp[5] = 0; dp[6] = 6;

	for(int round = round_spoken.size() + 1; round <= rounds; round++){
		dp[round] = round_spoken.find(dp[round-1]) == round_spoken.end() ? 0 : round - 1 - round_spoken[dp[round-1]];
		round_spoken[dp[round-1]] = round -1;
	}
	cout << dp.back() << endl;
}

int main(){
	ElfGame2(30000000);
	return 0;
}
