### [链接](https://www.luogu.com.cn/problem/P2093)
K-D Tree模板题。很显然，第 $k$ 小值可以利用堆轻松求出。

考虑将K-D Tree建出来后，找到每个节点包含的区间。如果某个节点所包含的区间中四个角处点（包括不存在的点）的距离最大值都没有堆中的第 $k$ 大大，那么这个节点就不用搜了。

显然，如果左子树的最大值比右子树大，那么先搜左子树再搜右子树效率平均来看较高。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
struct qdis{
	ll dis;
	int u;
	qdis(ll D=0,int U=0):dis(D),u(U){}
};
bool operator <(const qdis a,const qdis b){return a.dis>b.dis || (a.dis==b.dis && a.u<b.u);}
priority_queue<qdis>q;
bool cmpopt;
struct point{
	int x,y,id;
}p[N];
bool operator <(const point a,const point b)
{
	if(!cmpopt)return a.x<b.x;
	return a.y<b.y;
}
struct node{
	point p;
	ll mxx,mxy,mnx,mny;
	int ls,rs,id;
	void operator +=(node b)
	{
		mnx=min(mnx,b.mnx);mny=min(mny,b.mny);
		mxx=max(mxx,b.mxx);mxy=max(mxy,b.mxy);
	}
}t[N];
ll dis(node u,ll X,ll Y){return (u.p.x-X)*(u.p.x-X)+(u.p.y-Y)*(u.p.y-Y);}
ll getdis(node u,ll X,ll Y){return max((u.mxx-X)*(u.mxx-X),(u.mnx-X)*(u.mnx-X))+max((u.mxy-Y)*(u.mxy-Y),(u.mny-Y)*(u.mny-Y));}
void update(int u)
{
	if(!u) return;
	if(t[u].ls) t[u]+=t[t[u].ls];
	if(t[u].rs) t[u]+=t[t[u].rs];
}
void answer(int u,ll X,ll Y)
{
	if(!u) return;
	ll d=dis(t[u],X,Y);
	if(d>q.top().dis || (d==q.top().dis && t[u].id<q.top().u)) q.pop(),q.push((qdis){d,t[u].id});
	int l=t[u].ls,r=t[u].rs;
	ll ld,rd;
	if(l) ld=getdis(t[l],X,Y);
	if(r) rd=getdis(t[r],X,Y);
	if(ld>rd)
	{
		if(ld>=q.top().dis) answer(l,X,Y);
		if(rd>=q.top().dis) answer(r,X,Y);
	}
	else
	{
		if(rd>=q.top().dis) answer(r,X,Y);
		if(ld>=q.top().dis) answer(l,X,Y);
	}
}
int tot;
void build(int &u,int l,int r,bool k)
{
	if(l>r) return;
	u=++tot;
	cmpopt=k;
	int mid=(l+r)>>1;
	nth_element(p+l,p+mid,p+r+1);
	t[u].p=p[mid];
	t[u].id=t[u].p.id;
	t[u].mnx=t[u].mxx=t[u].p.x;
	t[u].mny=t[u].mxy=t[u].p.y;
	build(t[u].ls,l,mid-1,!k);
	build(t[u].rs,mid+1,r,!k);
	update(u);
}
int root;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].x,&p[i].y),p[i].id=i;
	build(root,1,n,false);
	int m;
	scanf("%d",&m);
	while(m --> 0)
	{
		ll X,Y,k;
		scanf("%lld%lld%lld",&X,&Y,&k);
		while(!q.empty()) q.pop();
		for(int j=1;j<=k;j++) q.push((qdis){-1,0});
		answer(root,X,Y);
		printf("%lld\n",q.top().u);
	}
	return 0;
}
```
