### [链接](https://www.luogu.com.cn/problem/CF283E)
考虑正难则反，用总方案 $C^3_n$ 减去不合法方案。

考虑一组不合法方案一定包含一头牛，满足这头牛大于另外两头牛。换句话说，一头牛大于另外两头牛，这组方案就不合法。

所以很明显可以得出不合法方案是 $\sum{C^{d_i}_{3}}$，设 $d_i$ 是第 $i$ 头牛大于的牛的个数。

一次区间取反很明显就是将答案也取反。考虑用权值线段树维护即可。

对于询问，直接离线，用双指针维护即可。

复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
int val[N<<2],tag[N<<2];
void set_tag(int u,int l,int r){val[u]=r-l+1-val[u];tag[u]^=1;}
void push_down(int u,int l,int r)
{
	if(!tag[u]) return;
	tag[u]^=1;
	int mid=(l+r)>>1;
	set_tag(u<<1,l,mid);
	set_tag(u<<1|1,mid+1,r);
}
void update(int u){val[u]=val[u<<1]+val[u<<1|1];}
void insert(int u,int l,int r,int L,int R)
{
	if(L<=l && r<=R){set_tag(u,l,r);return;}
	push_down(u,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) insert(u<<1,l,mid,L,R);
	if(R>mid) insert(u<<1|1,mid+1,r,L,R);
	update(u);
}
int answer(int u,int l,int r,int L,int R)
{
	if(L<=l && r<=R) return val[u];
	int v=0,mid=(l+r)>>1;
	push_down(u,l,r);
	if(L<=mid) v+=answer(u<<1,l,mid,L,R);
	if(R>mid) v+=answer(u<<1|1,mid+1,r,L,R);
	return v;
}
int num[N];
struct node{
	int l,r;
	bool operator <(const node a)const{return l<a.l;}
}a[N],b[N];
bool cmp(node a,node b){return a.r<b.r;}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	sort(num+1,num+n+1);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x=lower_bound(num+1,num+n+1,x)-num;
		y=upper_bound(num+1,num+n+1,y)-num-1;
		a[i].l=b[i].l=x,a[i].r=b[i].r=y;
	}
	sort(a+1,a+m+1);
	sort(b+1,b+m+1,cmp);
	int l=0,r=0;
	ll ans=1ll*n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++)
	{
		ll d=0;
		while(l<m && a[l+1].l<=i) ++l,insert(1,0,n,a[l].l,a[l].r);
		while(r<m && b[r+1].r<i) ++r,insert(1,0,n,b[r].l,b[r].r);
		if(i>1) d+=(i-1)-answer(1,0,n,1,i-1);
		if(i<n) d+=answer(1,0,n,i+1,n);
		ans-=d*(d-1)/2;
	}
	printf("%lld\n",ans);
	return 0;
}
```
