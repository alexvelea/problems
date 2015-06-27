//Problem d from mindcodingRound4
//"We are drowning in information and starved for knowledge."
#include <cassert>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#define int64 long long

const int inf = 0x3f3f3f3f;

struct Mat {
	int el[16][16];
	bool viz[16][16];

    int getNr(int a, int b) {
		int dx[4] = {0, 0, -1, +1};
		int dy[4] = {-1, +1, 0, 0};
		int rez = 1;
		viz[a][b] = true;
		for (int d = 0; d < 4; ++d) {
			int da = dx[d] + a;
			int db = dy[d] + b;
			if (viz[da][db] == false and el[da][db] == el[a][b]) {
				rez += getNr(da, db);
			}
		}
		return rez;
	}

	int getNr() {
		for (int i = 0; i < 16; ++i) 
			for (int j = 0; j < 16; ++j) {
				viz[i][j] = false;
			}
		return getNr(1, 1);
	}

	void fill(int x, int y, int init, int c) {
		if (el[x][y] == init) {
			el[x][y] = c;
 			int dx[4] = {0, 0, -1, +1};
			int dy[4] = {-1, +1, 0, 0};   		
 			for (int d = 0; d < 4; ++d) {
				int da = dx[d] + x;
				int db = dy[d] + y;   		
				if (el[da][db] == init) {
					fill(da, db, init, c);
				}
			}
		}
	}

	void fill(int c) {
		int init = el[1][1];
		if (init == c)
			return ;
		fill(1,1, init, c);
	}
};

int main() {
	Mat init;
	ios::sync_with_stdio(false);
	ifstream in("date.txt");
    for (int i = 1; i <= 14; ++i) {
		for (int j = 1; j <= 14; ++j) {
 			char c; cin >> c;
			int a = c - '0';
			init.el[i][j] = a;
		}
	}
	for (int i = 0; i < 16; ++i) {
		init.el[0][i] = init.el[15][i] = init.el[i][0] = init.el[i][15] = -1;
	}
	int rez = 0;
	while (1) {
		if (init.getNr() == 14 * 14) {
/*			if (rez > 25) 
				cerr << "1";
			cerr << '\t';*/
			
			return 0;
		}
	   
		int mx = 0, what = 0;
		for (int i = 0; i < 6 * 6 * 6 * 6 * 6; ++i) {
			int x[5] = {6,6,6,6,6}, ii = i, ind = 0;
			while (ii) {
				x[ind] = ii % 6;
				++ind;
				ii /= 6;
			}

			Mat aux = init;
			int raspuns = 0;
			for (int ind = 0; ind < 5; ++ind) {
				if (x[ind] == aux.el[1][1])
					break;
				aux.fill(x[ind]);
				if (aux.getNr() == 14 * 14) {
					raspuns = 1000 - ind;
				}
			}
			if (raspuns == 0)
				raspuns = aux.getNr();

            if (raspuns >= mx) {
				mx = raspuns;
				what = x[0];
			}
		}

		++rez;
		init.fill(what);
		cout << what << ' ';
/*		cerr << mx << '\t' << what << '\n';
		for (int i = 1; i <= 14; ++i, cout << '\n')
		for (int j = 1; j <= 14; ++j)
			cout << init.el[i][j];		
		cout << "\n\n";*/
	}
	return 0;
}
