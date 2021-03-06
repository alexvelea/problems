#include <cmath>
#include <cstdio>

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int max_n = 1000;
const float EPS = 0.0000001;

float cost[max_n][max_n];
int f[max_n][max_n], cap[max_n][max_n];
int n, x[max_n], y[max_n], sink, source, from[max_n];

vector<int> vertex[max_n];
float d[max_n];

bool get_flow() {

    int in_q[max_n];
	for (int i = 0 ; i < max_n; ++i) {
		in_q[i] = false;
		d[i] = 1000000.0;
		from[i] = 0;
	}

 	queue<int> q;
	q.push(source);
	in_q[source] = true;
	d[source] = 0;

	while (q.size()) {
		int nod = q.front();
		q.pop();
		if (nod == sink)
			continue;
		for (vector<int> :: iterator it = vertex[nod].begin(); it != vertex[nod].end(); ++it) 
			if ((d[*it] > d[nod] + cost[nod][*it] + EPS) && (cap[nod][*it] - f[nod][*it])) {
				from[*it] = nod;
				d[*it] = d[nod] + cost[nod][*it];
				if (!in_q[*it]) {
					q.push(*it);
					in_q[*it] = false;
				}
			}
	}
	if (from[sink])
		return true;
 	return false;
}


int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> x[i] >> y[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (y[i] < y[j]) {
				float dist = 1.0 * sqrt ((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
				cost[i][n+j] = dist;
				cost[n+j][i] = -dist;
				cap[i][j+n] = 1;
				vertex[i].push_back(n+j);
				vertex[n+j].push_back(i);
			}
	source = 2*n + 2;
	sink = 2*n + 3;
	for (int i = 1; i <= n; ++i) {
		cap[source][i] = 1;
		vertex[source].push_back(i);
		vertex[i].push_back(source);

		cap[n+i][sink] = 2;
 		vertex[n+i].push_back(sink);
		vertex[sink].push_back(n+i);
	}
	float flow_cost = 0;
	int flow;
	for (flow = 0; get_flow(); ++flow) {
		flow_cost += d[sink];
		int nod = sink;
		while (nod != source) {
            f[nod][from[nod]] --;
			f[from[nod]][nod] ++;
			nod = from[nod];
		}
	}
	if (flow != n-1) {
		cout << "-1";
		return 0;
	}
	printf("%.7f\n", flow_cost);
	return 0;
}
