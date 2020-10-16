### [链接](http://codeforces.com/problemset/problem/600/F)
结论题。

首先由一个结论：对于二分图的边染色，最小染色数等于点的最大入度。

证明好像有点复杂，但其实感性理解一下应该是这样。具体证明见 [神奇的论文](https://codeforces.com/blog/entry/75431)。

重点在于构造。可以发现，这题允许 $O(nm)$ 的构造。所以我们直接对于每条边，钦定一种颜色（最好是两端可行的某种颜色之一），然后暴力更改冲突部分。

由于这是一张二分图，所以这样每次更改最多 $O(n)$。

总复杂度 $O(nm)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define M 3010
using namespace std;
int u[N],v[N],deg[N];
int c[M][M];
int main()
{
	int a,b,m;
	scanf("%d%d%d",&a,&b,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]),v[i]+=a;
		deg[u[i]]++,deg[v[i]]++;
	}
	int cl=0,c1,c2;
	for(int i=1;i<=a+b;i++) cl=max(cl,deg[i]);
	for(int i=1;i<=m;i++)
	{
		for(c1=1;c1<=cl && c[u[i]][c1];c1++);
		for(c2=1;c2<=cl && c[v[i]][c2];c2++);
		c[u[i]][c1]=v[i];
		c[v[i]][c2]=u[i];
		if(c1==c2) continue;
		for(int c0=c2,x=v[i];x;x=c[x][c0],c0=(c0==c1?c2:c1)) swap(c[x][c1],c[x][c2]);
	}
	printf("%d\n",cl);
	for(int i=1;i<=m;i++)
	{
		for(c1=1;c1<=cl && c[u[i]][c1]!=v[i];c1++);
		printf("%d ",c1);
	}
	return 0;
}
```
