#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; ++qq) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> from(m), to(m), cost(m);
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
      cin >> from[i] >> to[i] >> cost[i];
      --from[i];
      --to[i];
      adj[from[i]].push_back(i);
      adj[to[i]].push_back(i);
    }
    vector<vector<pair<long long, pair<int, int>>>> cycles;
    vector<int> pe(n, -1);
    vector<int> depth(n);
    vector<bool> on(m);
    function<void(int)> dfs = [&](int x) {
      for (auto e : adj[x]) {
        if (e != pe[x]) {
          int y = from[e] + to[e] - x;
          if (!depth[y]) {
            depth[y] = depth[x] + 1;
            pe[y] = e;
            dfs(y);
          } else if (depth[x] < depth[y]) {
            vector<int> edges;
            int z = y;
            while (z != x) {
              edges.push_back(pe[z]);
              on[pe[z]] = true;
              z = from[pe[z]] + to[pe[z]] - z;
            }
            edges.push_back(e);
            on[e] = true;
            sort(edges.begin(), edges.end(), [&](int a, int b) {
              return cost[a] < cost[b];
            });
            cycles.emplace_back();
            cycles.back().emplace_back(cost[edges[0]] + cost[edges[1]], make_pair(edges[0], edges[1]));
            for (int i = 2; i < (int) edges.size(); ++i) {
              cycles.back().emplace_back(cost[edges[i]], make_pair(edges[i], -1));
            }
          }
        }
      }
    };
    int need = k;
    for (int i = 0; i < n; ++i) {
      if (!depth[i]) {
        depth[i] = 1;
        dfs(i);
        --need;
      }
    }
    need = max(need, 0);
    vector<int> edges;
    for (int i = 0; i < m; ++i) {
      if (!on[i]) {
        edges.push_back(i);
      }
    }
    sort(edges.begin(), edges.end(), [&](int a, int b) {
      return cost[a] < cost[b];
    });
    cycles.emplace_back();
    for (auto e : edges) {
      cycles.back().emplace_back(cost[e], make_pair(e, -1));
    }
    vector<vector<long long>> dp(cycles.size());
    for (int i = 0; i < (int) cycles.size(); ++i) {
      long long cur = 0;
      dp[i].push_back(cur);
      for (int j = 0; j < (int) cycles[i].size() && j < need; ++j) {
        cur += cycles[i][j].first;
        dp[i].push_back(cur);
      }
    }
    vector<int> left(cycles.size(), -1), right(cycles.size(), -1);
    set<pair<int, int>> huffman;
    for (int i = 0; i < (int) cycles.size(); ++i) {
      huffman.emplace(dp[i].size(), i);
    }
    while ((int) huffman.size() > 1) {
      int x = huffman.begin()->second;
      huffman.erase(huffman.begin());
      int y = huffman.begin()->second;
      huffman.erase(huffman.begin());
      int z = dp.size();
      dp.push_back(vector<long long>(min((int) dp[x].size() + (int) dp[y].size() - 1, need + 1), 1ll << 60));
      for (int i = 0; i < (int) dp[x].size(); ++i) {
        for (int j = 0; j < (int) dp[y].size(); ++j) {
          if (i + j <= need) {
            dp[z][i + j] = min(dp[z][i + j], dp[x][i] + dp[y][j]);
          }
        }
      }
      left.push_back(x);
      right.push_back(y);
      huffman.emplace(dp[z].size(), z);
    }
    vector<bool> bad(m);
    function<void(int, int)> push = [&](int z, int need) {
      if (!need) {
        return;
      }
      if (z < (int) cycles.size()) {
        for (int i = 0; i < need; ++i) {
          bad[cycles[z][i].second.first] = true;
          if (cycles[z][i].second.second != -1) {
            bad[cycles[z][i].second.second] = true;
          }
        }
      } else {
        int x = left[z];
        int y = right[z];
        for (int i = max(0, need - (int) dp[y].size() + 1); i < (int) dp[x].size() && i <= need; ++i) {
          if (dp[x][i] + dp[y][need - i] == dp[z][need]) {
            push(x, i);
            push(y, need - i);
            return;
          }
        }
      }
    };
    push(dp.size() - 1, need);
    cout << "Case " << qq << ": " << dp.back()[need] << "\n";
    vector<int> ans(n, -1);
    function<void(int, int)> color = [&](int x, int c) {
      ans[x] = c;
      for (auto e : adj[x]) {
        if (!bad[e]) {
          int y = from[e] + to[e] - x;
          if (ans[y] == -1) {
            color(y, c);
          }
        }
      }
    };
    int cur = 0;
    for (int i = 0; i < n; ++i) {
      if (ans[i] == -1) {
        color(i, cur++);
        if (cur == k) {
          cur = 0;
        }
      }
    }
  }
  return 0;
}