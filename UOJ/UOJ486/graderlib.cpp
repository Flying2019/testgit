#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#include "graph.h"

static const int maxn = 3010;

static int _n;
static bool _col[maxn + 5][maxn + 5];
static int _quota;

void init(int n, int k)  {
	_n = n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> _col[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			assert(_col[i][j] == _col[j][i]);
	for (int i = 1; i < k; ++i)
		assert(_col[i][i + 1] == 1);
	_quota = 0;
}

bool query(int u, int v) {
	++_quota;
	return _col[u][v];
}
