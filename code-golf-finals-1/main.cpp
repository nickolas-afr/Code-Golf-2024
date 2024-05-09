// I/O
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
// Containers
#include <list>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
// Other
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <tuple>
#include <cstring>
#include <string>
#include <utility>
#include <regex>
#define _CRT_SECURE_NO_DEPRECATE

using namespace std;

void f(vector<pair<string, string>> p)
{
	
	map<string, vector<string>> folder;
	map<string, int> hmf;
	stack<string>path;

	path.push("root");

	

	for (auto& it : p) {
		if (it.first == "mkf") {
				stack<string> temp;
				while (!path.empty()) {
					temp.push(path.top());
					hmf[path.top()]++;
					path.pop();
				}

				while (!temp.empty()) {
					path.push(temp.top());
					temp.pop();
				}
				folder[path.top()].push_back(it.second);
				path.push(it.second);
		}
		else if (it.first == "gb") {
			for(auto& dots : it.second) {
				if(path.top() != "root")
					path.pop();
			}
		}
		else if (it.first == "ps") {
			if (it.second == "_") {
				cout << path.top() << "*\n";
				for (auto& folders : folder[path.top()]) {
					cout << "|.." << folders << "\n";
				}
				if(!folder[path.top()].empty())
					cout << "\\\n";
			}
			else if (it.second[0] == '/') {
				stack<string> tempPath;
				tempPath.push("root");

				istringstream iss(it.second);
				string tok;
				while (getline(iss, tok, '/')) {
					if(tok != "")
						tempPath.push(tok);
				}

				if (tempPath.top() == path.top()) {
					cout << path.top() << "*\n";
					for (auto& folders : folder[path.top()]) {
						cout << "|.." << folders << "\n";
					}
					if (!folder[path.top()].empty())
						cout << "\\\n";
				}
				else {
					cout << tempPath.top() << "\n";
					for (auto& folders : folder[tempPath.top()]) {
						cout << "|.." << folders;
						if (folders == path.top()) {
							cout << "*";
						}
						cout << "\n";
					}
					if (!folder[tempPath.top()].empty())
						cout << "\\\n";
				}
			}
			cout << "\n";
		}
		else if (it.first == "ntd") {
			if (it.second[0] == '/') {
				istringstream iss(it.second);
				string tok;
				while (path.top() != "root") {
					path.pop();
				}
				while (getline(iss, tok, '/')) {
					if (tok != "")
					path.push(tok);
				}
			}
			else {
				path.push(it.second);
			}
		}
		else if (it.first == "dl") {
			string del = path.top();
			path.pop();
			folder[path.top()].erase(find(folder[path.top()].begin(), folder[path.top()].end(), del));
		}

		else if (it.first == "he") {
			if (it.second == "_") {
				cout << path.size() - 1 << "\n";
			}
			else if (it.second[0] == '/') {
				stack<string> tempPath;
				tempPath.push("root");

				istringstream iss(it.second);
				string tok;
				while (getline(iss, tok, '/')) {
					if (tok != "")
						tempPath.push(tok);
				}
				cout << tempPath.size() - 1 << "\n";
			}
			cout << "\n";
		}
		else if (it.first == "hmf") {
			if (it.second == "_") {
				if (path.top() == "root" && hmf[path.top()] == 1) {
					cout << hmf[folder["root"][0]] + 1 + 1 << "\n";
				}
				else
					cout << hmf[path.top()] + 1 << "\n";
				cout << "\n";
			}
			else {
				stack<string> tempPath;
				tempPath.push("root");

				istringstream iss(it.second);
				string tok;
				while (getline(iss, tok, '/')) {
					if (tok != "")
						tempPath.push(tok);
				}
				if (tempPath.top() == "root" && hmf[tempPath.top()] == 1) {
					cout << hmf[folder["root"][0]] + 1 + 1 << "\n";
				}
				else
					cout << hmf[tempPath.top()] + 1 << "\n";
				cout << "\n";
			}
		}

		else if (it.first == "srt") {
			if (it.second == "a") {
				sort(folder[path.top()].begin(), folder[path.top()].end());
			}
			else if (it.second == "d") {
				sort(folder[path.top()].begin(), folder[path.top()].end(), greater<string>());
			}
		}


	}
}

int main(int argc, char** argv)
{
	//ifstream in(argv[1]);
	//cin.rdbuf(in.rdbuf());

	int no;
	vector<pair<string, string>> v;
	cin >> no;
	for (int i = 0; i < no; i++)
	{
		pair<string, string> p;
		cin >> p.first >> p.second;
		v.push_back(p);
	}

	f(v);
	return 0;
}