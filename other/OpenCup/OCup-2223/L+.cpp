#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
template <typename T> void chkmin(T &x, T y) {x = min(x, y); }
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}
int n, m;
int x[MAXN], y[MAXN];
int f[MAXN], size[MAXN];
long long ans[MAXN];
int top, Stack[MAXN];
int comp, belong[MAXN];
int timer, dfn[MAXN], low[MAXN];
bool instack[MAXN];
vector <int> a[MAXN];
void tarjan(int pos) {
	dfn[pos] = low[pos] = ++timer;
	Stack[++top] = pos; instack[pos] = true;
	for (unsigned i = 0; i < a[pos].size(); i++)
		if (dfn[a[pos][i]] == 0) {
			tarjan(a[pos][i]);
			chkmin(low[pos], low[a[pos][i]]);
		} else if (instack[a[pos][i]]) chkmin(low[pos], dfn[a[pos][i]]);
	if (low[pos] == dfn[pos]) {
		int tmp = Stack[top--];
		instack[tmp] = false;
		comp = tmp;
		belong[tmp] = tmp;
		while (tmp != pos) {
			tmp = Stack[top--];
			instack[tmp] = false;
			belong[tmp] = comp;
		}
	}
}
int F(int x) {
	if (f[x] == x) return x;
	else return f[x] = F(f[x]);
}
int tot, col[MAXN];
void work(int l, int r, vector <int> e) {
	int mid = (l + r) / 2; tot++;
	vector <int> newpoint;
	for (unsigned i = 0; i < e.size(); i++)
		if (e[i] <= mid) {
			int tx = F(x[e[i]]), ty = F(y[e[i]]);
			if (col[tx] != tot) {
				col[tx] = tot;
				a[tx].clear();
				dfn[tx] = low[tx] = 0;
				newpoint.push_back(tx);
			}
			if (col[ty] != tot) {
				col[ty] = tot;
				a[ty].clear();
				dfn[ty] = low[ty] = 0;
				newpoint.push_back(ty);
			}
			a[tx].push_back(ty);
		}
	for (unsigned i = 0; i < newpoint.size(); i++)
		if (dfn[newpoint[i]] == 0) tarjan(newpoint[i]);
	if (l == r) {
		long long delta = 0;
		for (unsigned i = 0; i < newpoint.size(); i++) {
			int tmp = newpoint[i];
			if (F(tmp) != F(belong[tmp])) {
				delta += 1ll * size[F(belong[tmp])] * size[F(tmp)];
				size[F(belong[tmp])] += size[F(tmp)];
				f[F(tmp)] = F(belong[tmp]);
			}
		}
		ans[l] = ans[l - 1] + delta;
	} else {
		vector <int> el, er;
		for (unsigned i = 0; i < e.size(); i++) {
			int tx = F(x[e[i]]), ty = F(y[e[i]]);
			if (col[tx] == tot && col[ty] == tot && belong[tx] == belong[ty]) el.push_back(e[i]);
			else er.push_back(e[i]);
		}
		work(l, mid, el);
		work(mid + 1, r, er);
	}
}
int main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) {
		size[i] = 1;
		f[i] = i;
	}
	vector <int> tmp;
	for (int i = 1; i <= m; i++) {
		read(x[i]), read(y[i]);
		tmp.push_back(i);
	}
	work(1, m, tmp);
	for (int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
	return 0;
}