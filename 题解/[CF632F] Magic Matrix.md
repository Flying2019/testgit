### [链接](https://codeforces.com/contest/632/problem/F)
前两个限制可以很好解决。考虑这两个限制相当于什么：没有自环，图是完全图且均为双向边。

考虑第三个操作是什么意思：边 $(i,j)$ 不能被任意 $\max\{(i,k),(k,j)\}$ 代替。

取这样的边 $(i,j)$ 共 $n-1$ 条，这不就是最小生成树吗？

也就是说这个矩阵的任意一颗生成树都是最小生成树。

换句话说，所有同权值的边都可以作为生成树的一条边。

这样可以发现，我们排完序后把相同权值的拎出来，那么这些边应该全部可以被单独选中（忽略其他相同权值边的影响）。然后直接插入。

可以证明如果这样可行，那么任意一个生成树都是最小生成树。

复杂度 $O(n^2\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2510
using namespace std;
int num[N][N];
struct node{
	int x,y;
	bool operator <(const node a)const{return num[x][y]<num[a.x][a.y];}
	bool operator ==(const node a)const{return num[x][y]==num[a.x][a.y];}
}p[N*N];
int fa[N];
int find(int x){return x==fa[x]?fa[x]:(fa[x]=find(fa[x]));}
int main()
{
	int n,tot=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&num[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			if(i==j){if(num[i][j]){puts("NOT MAGIC");return 0;}}
			else if(num[i][j]!=num[j][i]){puts("NOT MAGIC");return 0;}
			else p[++tot]=(node){i,j};
		}
	sort(p+1,p+tot+1);
	for(int i=1;i<=n;i++) fa[i]=i;
	int l=1,r=1;
	for(;l<=tot;l=r)
	{
		for(;p[l]==p[r] && r<=tot;r++);
		for(int i=l;i<r;i++)
		if(find(p[i].x)==find(p[i].y)){puts("NOT MAGIC");return 0;}
		for(int i=l;i<r;i++) fa[find(p[i].x)]=find(p[i].y);
	}
	puts("MAGIC");
	return 0;
}
```
