#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1 << 18;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); }
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
int N, Log, P, G;
int power(int x, int y) {
	if (y == 0) return 1;
	int tmp = power(x, y / 2);
	if (y % 2 == 0) return 1ll * tmp * tmp % P;
	else return 1ll * tmp * tmp % P * x % P;
}
bool check(int g) {
	int tmp = P - 1, now = 2;
	while (now * now <= tmp) {
		if (tmp % now == 0) {
			while (tmp % now == 0) tmp /= now;
			if (power(g, (P - 1) / now) == 1) return false;
		}
		now++;
	}
	return true;
}
int home[MAXN];
void NTTinit() {
	for (int i = 0; i < N; i++) {
		int tmp = i, res = 0;
		for (int j = 1; j <= Log; j++) {
			res <<= 1;
			res += tmp & 1;
			tmp >>= 1;
		}
		home[i] = res;
	}
}
void NTT(int *a, int mode) {
	for (int i = 0; i < N; i++)
		if (home[i] > i) swap(a[i], a[home[i]]);
	for (int len = 2; len <= N; len <<= 1) {
		int delta = power(G, (P - 1) / len);
		if (mode == -1) delta = power(delta, P - 2);
		for (int i = 0; i < N; i += len) {
			int now = 1;
			for (int j = i, k = i + len / 2; k < i + len; j++, k++) {
				int tmp = a[j], tnp = 1ll * a[k] * now % P;
				a[j] = (tmp + tnp) % P;
				a[k] = (tmp - tnp + P) % P;
				now = 1ll * now * delta % P;
			}
		}
	}
	if (mode == -1) {
		int inv = power(N, P - 2);
		for (int i = 0; i < N; i++)
			a[i] = 1ll * a[i] * inv % P;
	}
}
void times(vector <int> a, vector <int> b, vector <int> &c) {
	assert(a.size() != 0 && b.size() != 0);
	int res = a.size() + b.size() - 2;
    if(res>=4096) cerr<<"mul "<<a.size()<<" "<<b.size()<<endl;
	for (N = 1, Log = 0; N <= res; N <<= 1, Log++);
	static int x[MAXN], y[MAXN];
	for (int i = 0; i < N; i++) {
		x[i] = y[i] = 0;
		if (i < a.size()) x[i] = a[i];
		if (i < b.size()) y[i] = b[i];
	}
	NTTinit(), NTT(x, 1), NTT(y, 1);
	for (int i = 0; i < N; i++)
		x[i] = 1ll * x[i] * y[i] % P;
	NTT(x, -1), c.clear();
	for (int i = 0; i <= res; i++)
		c.push_back(x[i]);
}
void update(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
void getinv(vector <int> a, vector <int> &b) {
	assert(a.size() != 0 && a[0] != 0);
	b.clear(), b.push_back(power(a[0], P - 2));
	while (b.size() < a.size()) {
		vector <int> tmpa, tmpb; times(b, b, tmpb);
		for (unsigned i = 0; i < b.size() * 2 && i < a.size(); i++)
			tmpa.push_back(a[i]);
		vector <int> res;
		times(tmpa, tmpb, res);
		b.resize(b.size() * 2);
		for (unsigned i = 0; i < b.size(); i++) {
			b[i] = 2ll * b[i] % P;
			if (i < res.size()) update(b[i], P - res[i]);
		}
	}
	b.resize(a.size());
}
int main() {
	int n; read(n), read(P), G = 2;
	while (!check(G)) G++;
	vector <int> res;
	res.push_back(0);
	res.push_back(1);
	while (res.size() <= n) {
		int goal = res.size() * 2;
		vector <int> sqr, cub, fur;
		times(res, res, sqr), sqr.resize(goal);
		times(sqr, res, cub), cub.resize(goal);
		times(cub, res, fur), fur.resize(goal);
		res.resize(goal);
		vector <int> func, der, inv;
		func.resize(goal), der.resize(goal);
		for (int i = 0; i < goal; i++) {
			func[i] = ((fur[i] + 2ll * sqr[i] - res[i] - (i != 0) * res[i - 1] + (i == 1)) % P + P) % P;
			der[i] = ((4ll * cub[i] + 4ll * res[i] - (i <= 1)) % P + P) % P;
		}
		getinv(der, inv);
		vector <int> mns;
		times(func, inv, mns);
		mns.resize(goal);
		for (int i = 0; i < goal; i++)
			update(res[i], P - mns[i]);
	}
		writeln(res[1]);
	return 0;
}