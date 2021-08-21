#include <bits/stdc++.h>
#define N 500005
#define int long long
using namespace std;

template <typename T>

void read(T &a)
{
	T x = 0,f = 1;
	register char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	a = x * f;
}

template <typename T>

void write(T x)
{
	if (x < 0) putchar('-'),x = -x;
	if (x < 10) return (void) putchar(x + '0');
	write(x / 10);
	putchar(x % 10 + '0');
}

template <typename T>

void writeln(T x)
{
	write(x);
	putchar('\n');
}

template <typename T>

void writes(T x)
{
	write(x);
	putchar(' ');
}

template <typename T,typename... Args>

void read(T &maxx,Args &... args)
{
	read(maxx);
	read(args...);
}

template <typename T,typename... Args>

void writeln(T maxx,Args ... args)
{
	writes(maxx);
	writes(args...);
	putchar('\n');
}

int n,m,head[N],pnt[N << 1],nxt[N << 1],E = 0;
int vis1[N],vis2[N],scc[N],sc_cnt = 0,sum = 0;
int from[N],to[N],val[N],fa[N];
struct link{int pre, nxt; }L[N];
struct edge
{
	int u,v,w;
	bool operator<(const edge &tmp) const
	{
		return w < tmp.w;
	}
};

int find(int x) {int u = x;while (u != fa[u]) u = fa[u] = fa[fa[u]]; return u;}
void del(int x){
    L[L[x].pre].nxt = L[x].nxt;
    L[L[x].nxt].pre = L[x].pre;
}

void add_edge(int u,int v)
{
	pnt[E] = v;
	nxt[E] = head[u];
	head[u] = E++;
}

void bfs()
{
	queue<int> q;
	while (L[0].nxt)
	{
		sc_cnt++;
		int now = L[0].nxt,cnt = 1;
		scc[now] = sc_cnt;
		q.push(now);
		del(now);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = head[u]; i != -1; i = nxt[i]) vis1[pnt[i]] = 1;
			for(int i = L[0].nxt; i; i = L[i].nxt)
			{
				if (!vis1[i] && !vis2[i])
				{
					vis2[i] = 1;
					q.push(i);
					cnt++;
					scc[i] = sc_cnt;
					del(i);
				}
			}
			for (int i = head[u]; i != -1; i = nxt[i]) vis1[pnt[i]] = 0;
		}
		sum += cnt * (cnt - 1) / 2 - cnt + 1;
	}
}

std::vector<int> e[N];

signed main()
{
	memset(head,-1,sizeof(head));
	read(n,m);
	int xorsum = 0;
	for (int i = 1; i <= m; i++)
	{
		read(from[i],to[i],val[i]);
		xorsum ^= val[i];
		int u = from[i],v = to[i];
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i = 1; i <= n; i++){
        L[i-1].nxt = i; L[i].pre = i - 1;
    } L[n].nxt = 0;
	bfs();
	std::vector<edge> qwq;
	int mini = 0x7f7f7f7f7f7f7f;
	for (int i = 1; i <= m; i++)
	{
		if (scc[from[i]] == scc[to[i]])
		{
			mini = min(mini,val[i]);
			continue;
		}
		qwq.push_back((edge) {scc[from[i]],scc[to[i]],val[i]});
	}
	sort(qwq.begin(),qwq.end());
	int ans = 0;
	iota(fa + 1,fa + sc_cnt,1);
	for (int i = 0; i < qwq.size(); i++)
	{
		int x = find(scc[qwq[i].u]),y = find(scc[qwq[i].v]);
		if (x == y) continue;
		ans += qwq[i].w;
		fa[x] = y;
	}
	if (m - qwq.size() == sum) ans += min(mini,xorsum);
	writeln(ans);
	return 0;
}