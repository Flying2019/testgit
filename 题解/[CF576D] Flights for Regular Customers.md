### [链接](https://codeforces.com/contest/576/problem/D)
考虑对边按 $d_i$ 排序，很显然应该从小到大插入 $d_i$ 的边（如果无法走则直接判无解）。

然后判断最短路。先判断经过 $t$ 条边能到哪些点，这个可以用矩阵快速幂解决。然后判断从这些点到 $n$ 的最短路即可。

考虑时间复杂度为 $O(n^3m\log t)$，不够优秀。

可以发现矩阵本质上是一个01矩阵，直接bitset优化即可，复杂度 $O(\frac{n^3m\log t}{\omega})$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<queue>
#include<algorithm>
#define N 150
#define Bt bitset<N>
#define ll long long
#define inf 100000000000000ll
using namespace std;
struct road{
	int x,y,w;
	bool operator <(const road a)const{return w<a.w;}
}rd[N];
int n;
struct matrix{
	Bt num[N];
	Bt& operator [](int a){return num[a];}
	matrix operator *(matrix a)
	{
		matrix b;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			if(num[i][j]) b[i]|=a[j];
		return b;
	}
}a;
Bt operator *(Bt a,matrix b)
{
	Bt c;
	for(int i=0;i<n;i++) c[i]=(a&b[i]).any();
	return c;
}
void ksm(matrix a,int b,Bt &r)
{
	for(;b;b>>=1)
	{
		if(b&1) r=r*a;
		a=a*a;
	}
}
Bt r;
ll dis[N],ans=inf;
queue<int>q;
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		--u,--v;
		rd[i]=(road){u,v,w};
	}
	sort(rd+1,rd+m+1);
	r[0]=1;
	int t=0;
	for(int i=1;i<=m;i++)
	{
		if(rd[i].w>=ans) break;
		int k=rd[i].w-t;
		ksm(a,k,r);
		a[rd[i].y][rd[i].x]=1;
		t=rd[i].w;
		for(int j=0;j<n;j++)
		if(r[j]) q.push(j),dis[j]=0;
		else dis[j]=inf;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int v=0;v<n;v++)
			if(a[v][u])
			{
				if(dis[v]>dis[u]+1)
				dis[v]=dis[u]+1,q.push(v);
			}
		}
		ans=min(ans,t+dis[n-1]);
	}
	if(ans>=inf) puts("Impossible");
	else printf("%lld",ans);
	return 0;
}
```
