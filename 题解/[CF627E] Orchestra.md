### [链接](https://codeforces.com/problemset/problem/627/E)
考虑一个 $O(n^3)$ 的暴力：每次枚举一个矩形的上边界和下边界，中间通过双指针 $O(n)$ 处理，总复杂度 $O(n^3)$。

但是这个显然不能通过此题（不知道能不能卡卡常过去）。考虑优化。

观察题目，发现 $k$ 特别得小。所以考虑用一些手段把一个 $n$ 换成 $k$。

考虑我们收缩下边界的时候，删的总点数是 $O(n)$ 的，而一次删除总的改变的区间数是 $O(k)$ 的，也就是其余的区间不受影响。

那么我们考虑我们要删除点 $u$ ，假如我们能求出 $r=u$ 时最大的 $l$ 使 $[l,r]$ 中有 $k$ 个点，然后模拟双指针的过程把区间贡献扫掉，然后删除 $u$ 点，重新计算上述区间即可。

那么这样我们需要支持 $O(k)$ 回溯，$O(1)$ 插入/删除。这显然可以用双向链表实现。

具体细节很多，比如撤销贡献时要找再左边一个，因为这个区间虽然大小不受影响，但是方案数受影响。

时间复杂度 $O(n^2k)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define ll long long
#define N 3010
using namespace std;
int x[N],y[N];
vector<int>py[N];
int L[N],R[N],q,k;
void nxt(int &u,int k=1){while(k --> 0) u=R[u];}
void pre(int &u,int k=1){while(k --> 0) u=L[u];}
ll res=0;
struct node{
	int x,y;
	bool operator <(const node a)const{return x<a.x;}
}p[N];
int n,m;
void solve()
{
	res=0;
	int l=0,r=0;
	nxt(r,k);
	if(r==q+1) return;
	for(;r!=q+1;nxt(r))
	{
		nxt(l);
		res+=1ll*p[l].x*(p[R[r]].x-p[r].x);
	}
}
void del(int u){R[L[u]]=R[u],L[R[u]]=L[u];}
void erase(int u)
{
	int l=u;pre(l,k+1);int l0=l;
	int r=l;nxt(r,k);
	for(;l<u && r<q+1;nxt(r))
	{
		nxt(l);
		res-=1ll*p[l].x*(p[R[r]].x-p[r].x);
	}
	del(u);
	l=r=l0;nxt(r,k);
	for(;R[l]<u && r<q+1;nxt(r))
	{
		nxt(l);
		res+=1ll*p[l].x*(p[R[r]].x-p[r].x);
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&q,&k);
	for(int i=1;i<=q;i++) scanf("%d%d",&p[i].x,&p[i].y);
	sort(p+1,p+q+1);
	p[q+1]=(node){n+1,m+1};
	for(int i=1;i<=q;i++) py[p[i].y].push_back(i);
	ll ans=0;
	R[q+1]=q+1;
	for(int y0=1;y0<=m;y0++)
	{
		int pr=0;
		for(int i=1;i<=q;i++) if(p[i].y<=y0) L[i]=pr,pr=i;else L[i]=0;
		L[q+1]=pr;
		pr=q+1;
		for(int i=q;i>=1;i--) if(p[i].y<=y0) R[i]=pr,pr=i;else R[i]=0;
		R[0]=pr;
		solve();
		ans+=res;
		for(int y=1;y<=y0;y++)
		{
			for(int u:py[y]) erase(u);
			ans+=res;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
