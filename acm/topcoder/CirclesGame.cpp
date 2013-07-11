#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

const int MAX = 55;

int n;
int has[MAX][MAX], has_clo[MAX][MAX];
int par[MAX];
vector<int> g[MAX];

bool contain(int x1, int y1, int r1, int x2, int y2, int r2) {
    return r1 > r2 && ((r1 - r2) * (r1 - r2) >= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool legal(int sub, int from, int to) {
    return sub == to || (has_clo[from][sub] && has_clo[sub][to]);
}

int solve(int from) {
    if (sg[from] != -1) {
	return sg[from];
    }
    int & ret = sg[from];
    vector<int> ne;

    int to, sub;
    for (to = 0; to < n; to++) {
	int tmp_val = 0;
	if (has_clo[from][to]) {
	    for (sub = 0; sub < n; sub ++) {
		if (!legal(sub, from, to)) {
		    int sub_par = par[sub];
		    if (sub_par != -1 && legal(sub_par, from, to)) {
			tmp_val ^= solve(sub);
		    }
		}
	    }
	}
	ne.push_back(tmp_val);
    }

    return ret;
}

class CirclesGame {
    public:
    string whoCanWin(vector<int> x, vector<int> y, vector<int> r) {
	memset(par, -1, sizeof(par));
	n = x.size();
	int i, j, k;
	for (i = 0; i < n; i++) {
	    has_clo[i][i] = 1;
	    for (j = 0; j < n; j++) {
		if (contain(x[i], y[i], r[i], x[j], y[j], r[j])) {
		    has[i][j] = has_clo[i][j] = 1;
		}
	    }
	}
	for (k = 0; k < n; k++) {
	    for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
		    if (k == i || k == j || i == j) {
			continue;
		    }
		    if (has_min[i][k] && has_min[k][j]) {
			has_min[i][j] = 0;
		    }
		}
	    }
	}

	for (i = 0; i < n; i++) {
	    for (j = 0; j < n; j++) {
		if (has[i][j]) {
		    g[i].push_back(j);
		    par[j] = i;
		}
	    }
	}

	int ans = 0;

	memset(sg, -1, sizeof(sg));

	for (i = 0; i < n; i++) {
	    if (par[i] == -1) {
		int tmp = solve(i);
		ans = ans ^ tmp;
	    }
	}

	if (ans) {
	    return "Alice";
	} else {
	    return "Bob";
	}
    }
};
