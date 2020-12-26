#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef unsigned long long ull;

int FindLast(int start, string problem){
	int count = 0;
	for(int i = start; i < problem.size(); i++){
		char c = problem[i];
		count += (c == '(' ? 1 : (c == ')' ? -1 : 0));
		if(count < 0) return i;
	}
	return -1;
}

ull Evaluate(string problem){
	//cout << problem << endl;
	stringstream ss(problem);
	string feed;
	ull prev_operand = 0;
	char prev_operator = '+';
	ull result;
	while(ss >> feed){
		if(feed.front() == '('){
			//start from after the parenthesis of the feed
			int start = (int)ss.tellg() - feed.size() + 1;
			int end = FindLast(start, problem);
			switch(prev_operator){
				case '+':
					result = prev_operand + Evaluate(problem.substr(start,end-start));
					break;
				case '*':
					result = prev_operand * Evaluate(problem.substr(start,end-start));
					break;
				default:
					break;
			}
			prev_operand = result;
			ss.seekg(end+1);
		}
		else if(feed[0] == '*' || feed[0] == '+'){
			prev_operator = feed[0];
		}
		else{
			//cout << feed << endl;
			if(feed.find(")") == 0) continue;
			ull next_operand = stoull(feed);
			switch(prev_operator){
				case '+':
					result = prev_operand + next_operand;
					break;
				case '*':
					result = prev_operand * next_operand;
					break;
				default:
					break;
			}
			prev_operand = result;
		}
	}
	cout << "return: " << prev_operand << endl;
	return prev_operand;
}


//At this stage, there should only be multiplication
string Multiply(string problem){
	stringstream ss(problem);
	string term;
	ull operand = 1;
	while(ss >> term){
		if(term != "*") operand *= stoull(term);
	}
	//cout << "after multiplying: " << operand << endl;
	return to_string(operand);
}

//At this stage, there shouldn't be any parenthesis in the problem
string Add(string problem){
	stringstream ss(problem);
	ull operand = 0;
	char prev_operator = '+';
	string simplified;
	string term;
	while(ss >> term){
		if(term == "*"){
			prev_operator = term[0];
			simplified += to_string(operand) + " " + term + " ";
			operand = 0;
		}
		else if(term == "+"){
			prev_operator = term[0];
		}
		else{
			operand += stoull(term);
		}
	}
	if(operand) simplified += to_string(operand);
	else simplified.pop_back();
	//cout << "After adding: " << simplified << endl;
	return simplified;
}

string EvaluateAdvanced(string problem);
string Reduce(string problem){
	int start;
	while((start = problem.find("(")) != string::npos){
		int end = FindLast(start+1, problem);
		//cout << "end: " << end << endl;
		problem = problem.substr(0,start) + EvaluateAdvanced(problem.substr(start+1,end-(start+1))) + problem.substr(end+1);
		//cout << "After reducing parenthesis: " << problem << endl;
	}
	return problem;
}

string EvaluateAdvanced(string problem){
	cout << "problem: " << problem << endl;
	string simplified = Multiply(Add(Reduce(problem)));
	cout << simplified << endl;
	return simplified;
}
int main(){
	ifstream input_file("day18.txt");
	string problem;
	ull sum = 0;
	while(getline(input_file,problem)){
		//sum += Evaluate(problem);
		sum += stoull(EvaluateAdvanced(problem));
	}
	cout << sum << endl;
	return 0;
}
