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
#include "graderlib.cpp"

int main() 
{
	int n, k;
	assert(scanf("%d%d", &n, &k) == 2);
	init(n, k);
	vector<int> out = find_longer_path(n, k);
	printf("number of queries: %d\n", _quota);
	printf("your route:");
	REP(i, 0, SZ(out)) printf(" %d", out[i]);
	printf("\n");
    return 0;
}
