### [链接](http://codeforces.com/problemset/problem/581/F)
无脑树形dp。

用 $f_{i,j,0/1}$ 表示 $i$ 子树内有 $j$ 个黑点，$i$ 点为白/黑时的最小不同颜色数。

显然可以用类似于背包的方式树形dp。

我们只需要取最后 $j=\text{叶子数}$ 时的结果即可。复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 5010
#define inf 100000000
using namespace std;
int f[N][N][2],swp[N][2],lev;
int deg[N];
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	deg[u]++;
}
int siz[N];
void dfs(int u,int pre)
{
	if(deg[u]==1){f[u][0][0]=f[u][1][1]=0,siz[u]=1;return;}
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==pre) continue;
		dfs(v,u);
		if(!siz[u]){for(int j=0;j<=siz[v];j++) for(int _=0;_<=1;_++) f[u][j][_]=min(f[v][j][_],f[v][j][!_]+1);}
		else 
		{
			for(int j=0;j<=min(siz[u],lev);j++)
				for(int _=0;_<=1;_++) swp[j][_]=f[u][j][_],f[u][j][_]=inf;
			for(int j=0;j<=min(siz[u],lev);j++)
				for(int k=0;k<=min(siz[v],lev-j);k++)
					for(int _=0;_<=1;_++)
					f[u][j+k][_]=min(f[u][j+k][_],swp[j][_]+min(f[v][k][_],f[v][k][!_]+1));
		}
		siz[u]+=siz[v];
	}
}
int main()
{
	memset(f,60,sizeof(f));
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++) lev+=deg[i]==1;
	lev/=2;
	int rt=0;
	for(int i=1;i<=n;i++) if(deg[i]!=1){rt=i;break;}
	dfs(rt,0);
	printf("%d",min(f[rt][lev][0],f[rt][lev][1]));
	return 0;
}
```
