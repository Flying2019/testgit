### [链接](http://codeforces.com/problemset/problem/605/E)
考虑倒着做。类似于dijkstra,，处理出从某一点开始到 $n$ 期望距离最短的一个点。

考虑题目要求“最优策略”，就是走到期望距离最短的那一个点。

直接处理即可。复杂度 $O(n^2)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define db double
#define N 1010
using namespace std;
db f[N],p[N][N],sum[N],dis[N];
bool vis[N];
int q[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		sum[i]=f[i]=1;
		for(int j=1;j<=n;j++)
		scanf("%lf",&p[i][j]),p[i][j]*=0.01;
	}
	vis[n]=true;
	int pre=n;
	for(int i=2;i<=n;i++)
	{
		int u=pre;
		for(int j=1;j<=n;j++)
		if(!vis[j])
		{
			sum[j]+=dis[u]*p[j][u]*f[j];
			f[j]*=(1-p[j][u]);
			dis[j]=sum[j]/(1-f[j]);
		}
        u=0;
        for(int j=1;j<=n;j++)
        if(!vis[j] && (!u || dis[u]>dis[j])) u=j;
        vis[u]=true;
        pre=u;
	}
	printf("%.8lf",dis[1]);
	return 0;
}

```
