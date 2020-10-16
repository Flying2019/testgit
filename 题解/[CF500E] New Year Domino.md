### [链接](https://codeforces.com/contest/500/problem/E)
考虑一个性质：假如我们让区间 $[l,r]$ 的所有多米诺全部倒下，可以发现空出来的空间就是答案。

所以我们倒序插入每个多米诺。那么需要支持维护区间赋1，区间求0个数。这个随便什么数据结构都可以维护。

然后将询问离线。可以发现对于右端点 $r$ ，在 $r$ 之后的多米诺不会对 $r$ 之前的区域造成影响。所以直接在插入 $l$ 时查询 $[l,r]$ 的结果即可。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
ll val[N*40];
int ls[N*40],rs[N*40],cnt;
void insert(int &u,ll l,ll r,ll L,ll R)
{
	if(!u) u=++cnt;
	if(val[u]==r-l+1) return;
	if(L<=l && r<=R){val[u]=r-l+1;return;}
	ll mid=(l+r)>>1;
	if(L<=mid) insert(ls[u],l,mid,L,R);
	if(R>mid) insert(rs[u],mid+1,r,L,R);
	val[u]=val[ls[u]]+val[rs[u]];
}
ll answer(int u,ll l,ll r,ll L,ll R)
{
	if(R<L) return 0;
	if(val[u]==r-l+1) return R-L+1;
	if(!val[u] || (L<=l && r<=R)) return val[u];
	int mid=(l+r)>>1;
	if(L>mid) return answer(rs[u],mid+1,r,L,R);
	if(R<=mid) return answer(ls[u],l,mid,L,R);
	return answer(ls[u],l,mid,L,mid)+answer(rs[u],mid+1,r,mid+1,R);
}
ll l[N],r[N];
struct ques{
	ll l,r,id;
	bool operator <(const ques a)const{return l>a.l;}
}q[N];
ll ans[N];
int main()
{
	int n,m;
	scanf("%d",&n);
	ll maxn=0;
	for(int i=1;i<=n;i++) scanf("%lld%lld",&l[i],&r[i]),r[i]+=l[i]-1,maxn=max(maxn,r[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%lld%lld",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int u=1,root=0;
	for(int i=n;i>=1;i--)
	{
		insert(root,1,maxn,l[i],r[i]);
		for(;q[u].l==i;u++)
		{
			ll d=l[q[u].r]-r[q[u].l];
			if(d<0) ans[q[u].id]=0;
			else ans[q[u].id]=d-answer(root,1,maxn,r[q[u].l],l[q[u].r])+1;
		}
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```
