### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102652/problem/C)
### 题目大意
给定一个序列 $a_i$ 和 $x$，你可以选择至多 $k$ 个互不相交区间，将区间中的数 $\times x$。求最大子段和。
### 题解
考虑dp。用 $f_{i,j}$ 表示当前点 $i$ 被区间包含($\times x$)时的最优结果。用 $g_{i,j}$ 表示当前点 $i$ 没被区间包含时的最优结果。

显然可得转移方程，直接转移即可。复杂度 $O(nm)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 300010
#define M 32
#define ll long long
using namespace std;
ll f[2][M],g[2][M],val[N];
int main()
{
	int n,m,x;
	scanf("%d%d%d",&n,&m,&x);
	for(int i=1;i<=n;i++) scanf("%lld",&val[i]);
	int u=0;
	for(int i=0;i<=m;i++) f[0][i]=g[0][i]=-1000000000000ll;
	ll ans=-1000000000000ll;
	for(int i=1;i<=n;i++)
	{
		int p=u;
		u=!u;
		for(int j=0;j<=m;j++) f[u][j]=g[u][j]=-1000000000000ll;
		f[u][1]=val[i]*x,g[u][0]=val[i];
		for(int j=0;j<=m;j++)
		{
			if(j)f[u][j]=max(f[u][j],f[p][j]+val[i]*x),f[u][j]=max(f[u][j],g[p][j-1]+val[i]*x);
			g[u][j]=max(g[u][j],f[p][j]+val[i]);
			g[u][j]=max(g[u][j],g[p][j]+val[i]);
		}
		for(int j=0;j<=m;j++)
		ans=max(ans,max(f[u][j],g[u][j]));
	}
	printf("%lld\n",ans);
	return 0;
}
```
