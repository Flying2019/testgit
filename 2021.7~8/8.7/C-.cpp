#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define setIO(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define closefile fclose(stdin), fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr << x << " "
#define seeln(x) cerr << x << endl
#define out(x) cerr << #x << " = " << x << " "
#define outln(x) cerr << #x << " = " << x << endl
#define outarr(x, l, r) {cerr << #x"[" << l << " ~ " << r << "] = "; for (int _i = l; _i <= r; ++_i) cerr << x[_i] << " "; cerr << endl;}
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
//#define gc getchar()
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
template <class T> void read(T &x)
{
    x = 0; int c = gc;
    while (c < '0' || c > '9') c = gc;
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = gc;
}
template <class T> bool checkmax(T &a, T b){return a < b ? a = b, 1 : 0;}
template <class T> bool checkmin(T &a, T b){return b < a ? a = b, 1 : 0;}
int n, m;
int x1, x2;
//(1, x1), (n, x2)
void init()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d", &x1, &x2);
}

int doit(int p, int q)
{
    //max(i + 1 - abs(p - x1), 0) + max(i + 1 - abs(q - x2), 0);
    int l = 0, r = min(n - 1, m - 1), mid, best = -1;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (max(mid + 1 - abs(p - x1), 0) + max(mid + 1 - abs(q - x2), 0) >= n) best = mid, r = mid - 1;
        else l = mid + 1;
    }
    if (best == -1) return min(n - 1, m - 1);
    return best;
}

int calc()
{
    int ans = min(n - 1, m - 1);
    checkmin(ans, abs(1 - 1) + abs(x1 - 1));
    checkmin(ans, abs(n - 1) + abs(x2 - 1));
    checkmin(ans, abs(1 - n) + abs(x1 - m));
    checkmin(ans, abs(n - n) + abs(x2 - m));
    checkmin(ans, doit(x1, x1));
    if (x1 < n) checkmin(ans, doit(x1, x1 + 1));
    if (x1 > 1) checkmin(ans, doit(x1, x1 - 1));
    checkmin(ans, doit(x2, x2));
    if (x2 < n) checkmin(ans, doit(x2 + 1, x2));
    if (x2 > 1) checkmin(ans, doit(x2 - 1, x2));
    return ans;
}

void solve()
{
    int sum = calc();
    printf("%lld\n", (ll)sum * sum);
}

int main()
{
    int t; scanf("%d", &t); while (t--)
    {
        init();
        solve();
    }
    return 0;
}