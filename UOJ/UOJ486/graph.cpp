#include <bits/stdc++.h>

using namespace std;

#include "graph.h"

vector<int> find_longer_path(int n, int k) {
	vector<int> res;
	if (query(k, k + 1) == 1)
		for (int i = 1; i <= k + 1; i++) 
			res.push_back(i);
	return res;
}
