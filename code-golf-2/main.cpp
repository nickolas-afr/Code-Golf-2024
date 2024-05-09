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


struct w {
	int n;
	int m;
	int vn;
	int vm;
	int s;
};

struct o {
	char t;
	int x1;
	int y1;
	int x2;
	int y2;
};

struct b {
	int x;
	int y;
	int d;
	int p;
};

void f(w w, vector<o> o, vector<b> b)
{
	static int tries = b.size();
	static int score = 0;

	static int k = 0;

	static vector<pair<int, int>> obsPos;
	static vector<char> obsType;

	for (auto& it : o) {
		obsPos.push_back(make_pair(it.x1, it.x2));
		obsType.push_back(it.t);
	}

	//auto ball = b.begin();
	if(tries) {

		cout << '[';
		for (int j = 1; j <= w.m; j++) {
			cout << '=';
		}
		cout << "]\n";

		for (int i = 1; i <= w.n; i++) {
			cout << '[';
			for (int j = 1; j <= w.m; j++) {
				bool printStar = false;
				bool printObs = false;
				char temp;
				if (b[k].x == i && b[k].y == j) {
					printStar = true;
				}
				for (auto& it : o) {
					if (it.x1 == i && it.y1 == j) {
						//cout << it.t;
						temp = it.t;
						printObs = true;
					}
				}
				
				if (printStar && printObs) {
					cout << '+';
				}
				else if (printStar) {
					cout << '*';
				}
				else if (printObs) {
					cout << temp;
				}
				else {
					cout << '.';
				}
			}
			cout << "]\n";
		}
		cout << '[';
		for (int j = 1; j <= w.m; j++) {
			cout << '=';
		}
		cout << "]\n";
		cout << "Tries: " << tries << '\n';
		cout << "Score: " << score << "\n\n";

		//directions
		if (b[k].d == 0) {
			if (b[k].p) {
				b[k].x--;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 1) {
			if (b[k].p) {
				b[k].y++;
				b[k].x--;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 2) {
			if (b[k].p) {
				b[k].y++;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 3) {
			if (b[k].p) {
				b[k].y++;
				b[k].x++;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 4) {
			if (b[k].p) {
				b[k].x++;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 5) {
			if (b[k].p) {
				b[k].y--;
				b[k].x++;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 6) {
			if (b[k].p) {
				b[k].y--;
				b[k].p--;
			}
			else
				b[k].x++;
		}
		else if (b[k].d == 7) {
			if (b[k].p) {
				b[k].y--;
				b[k].x--;
				b[k].p--;
			}
			else
				b[k].x++;
		}

		if (b[k].x > w.n) {
			tries--;
			k++;
		}
		else if (b[k].x <= 0) {			//ball bounces off top wall
			if (b[k].y <= 0) {			//ball bounces off top wall AND left wall
				b[k].y += 2;
				b[k].x += 2;
				b[k].d = 3;
			}
			else if (b[k].y > w.m) {	//ball bounces off top wall AND right wall
				b[k].y -= 2;
				b[k].x += 2;
				b[k].d = 5;
			}
			else {
				b[k].x += 2;
				if (b[k].d == 0) {
					b[k].d = 4;
				}
				if (b[k].d == 1) {
					b[k].d = 3;
				}
				else if (b[k].d == 7) {
					b[k].d = 5;
				}
			}
		}
		else if (b[k].y > w.m) { //ball bounces off right wall
			b[k].y -= 2;
			b[k].d = 8 - b[k].d;
		}
		else if (b[k].y <= 0) {	//ball bounces off left wall
			b[k].y += 2;
			b[k].d = 8 - b[k].d;
		}
		else {
			for (auto& it : o) {
				if (it.x1 == b[k].x && it.y1 == b[k].y) {
					if (b[k].d == 1 || b[k].d == 2 || b[k].d == 3) {
						if (b[k].d == 1)
							b[k].x--;
						else if (b[k].d == 3)
							b[k].x++;
						else if (b[k].d == 2)
							b[k].y--;
						b[k].y--;;
						b[k].d = 8 - b[k].d;
					}
					else if(b[k].d == 5 || b[k].d == 6 || b[k].d == 7){
						if (b[k].d == 7)
							b[k].x--;
						else if (b[k].d == 5)
							b[k].x++;
						else if (b[k].d == 6)
							b[k].y++;
						b[k].y++;
						b[k].d = 8 - b[k].d;
					}
				}
			}
		}

		f(w, o, b);
	}
	else{
		cout << "Oops! Looks like you ran out of tries...\n";
		cout << "Game over!\n";
		cout << "Tries: " << tries << '\n';
		cout << "Score: " << score << '\n';
		return;
	}
}

int main(int argc, char** argv)
{

	//cin.rdbuf(cin.rdbuf());

	w w;
	int no, nb;
	vector<o> vo;
	vector<b> vb;

	cin >> w.n >> w.m >> w.vn >> w.vm >> w.s;
	cin >> no;
	for (int i = 0; i < no; i++)
	{
		o o;
		cin >> o.t >> o.x1 >> o.y1 >> o.x2 >> o.y2;
		vo.push_back(o);
	}
	cin >> nb;
	for (int i = 0; i < nb; i++)
	{
		b b;
		cin >> b.x >> b.y >> b.d >> b.p;
		vb.push_back(b);
	}

	f(w, vo, vb);

}