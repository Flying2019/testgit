### [链接](https://codeforces.com/problemset/problem/232/E)
首先显然有一个 $O(qnm)$ 的dp，而且显然过不去。

考虑如何优化。可以发现 $n,m$ 都很小，而 $q$ 很大。所以先离线所有询问。

可以发现，假如存在某一个点 $(x\in[x_l,x_r],y\in[y_l,y_r])$，使 $(x_l,x_r)$ 能到 $(x,y)$，$(x,y)$ 能到 $y_l,y_r$，那么一定可行。

而且这样的点对于所有 $x\in[x_l,x_r]$ 都至少存在一个 $y\in[y_l,y_r]$ 满足条件。

所以我们不妨二分 $x$，令 $f_{i,j,k}$ 表示点 $(i,j)$ 能否到达 $(x,k)$，$g_{i,j,k}$ 表示点 $(i,j)$ 能否到达 $(x,k)$。转移显然。

可以发现，对于询问 $(x_l\leq x,y_l,x_r\geq x,y_r)$，可行当且仅当存在 $k$，使 $f_{x_l,y_l,k}=1$ 且 $g_{x_r,y_r,k}=1$。

如果 $[x_l,x_r]$ 没有跨越 $x$，那么我们递归左右的 $x$，继续处理。

时空复杂度 $O(qn+n^3\log n)$。空间会炸。

所以考虑用bitset优化 $f,g$，时空复杂度均为 $O(\frac{qn+n^3\log n} {\omega})$，可以通过。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>
#define N 600010
#define M 510
using namespace std;
bitset<M> f[M][M],g[M][M];
struct ques{
	int xl,yl,xr,yr,id;
}q[N];
vector<int>p;
int ans[N],n,m;
char mp[M][M];
void work(int l,int r,vector<int>& p)
{
	if(l>r || p.empty()) return;
	int mid=(l+r)>>1;
	for(int i=1;i<=m;i++) f[mid][i].reset(),g[mid][i].reset();
	for(int i=m;i>=1;i--)
		if(mp[mid][i]=='.') f[mid][i][i]=1,f[mid][i]|=f[mid][i+1];
	for(int i=1;i<=m;i++)
		if(mp[mid][i]=='.') g[mid][i][i]=1,g[mid][i]|=g[mid][i-1];
	for(int i=mid-1;i>=l;i--)
		for(int j=m;j>=1;j--)
		f[i][j]=(mp[i][j]=='.')?f[i+1][j]|f[i][j+1]:0;
	for(int i=mid+1;i<=r;i++)
		for(int j=1;j<=m;j++)
		g[i][j]=(mp[i][j]=='.')?g[i-1][j]|g[i][j-1]:0;
	vector<int>pl,pr;
	for(int i=0;i<p.size();i++)
	{
		if(q[p[i]].xr<mid){pl.push_back(p[i]);continue;}
		if(q[p[i]].xl>mid){pr.push_back(p[i]);continue;}
		ans[p[i]]=(f[q[p[i]].xl][q[p[i]].yl]&g[q[p[i]].xr][q[p[i]].yr]).any();
	}
	work(l,mid,pl);
	work(mid+1,r,pr);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
	int qn;
	scanf("%d",&qn);
	for(int i=1;i<=qn;i++) scanf("%d%d%d%d",&q[i].xl,&q[i].yl,&q[i].xr,&q[i].yr);
	for(int i=1;i<=qn;i++) p.push_back(i);
	work(1,n,p);
	for(int i=1;i<=qn;i++) puts(ans[i]?"Yes":"No");
	return 0;
}
```
