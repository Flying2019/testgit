### [链接](https://codeforces.com/contest/603/problem/E)
略加观察可以发现，每个点的度数是奇数成立当且仅当对于任意连通块，其点数 $a$ 为偶数。

因为如果存在点数 $a$ 为奇数的连通块，显然其中有偶数个奇节点，那么一定有至少一个偶节点。

否则一定存在一种方案，使每个结点均为奇数。

可以发现，对于一条边，如果其是最大值，那么所有小于等于它的边都可以加入。而我们显然有加入越多的边，越有可能成功。、

如果我们把询问离线，把询问看成一个维度，那么一次询问就是只考虑时间 $\leq t$，权值 $\leq w$ 的边能否成立。

可以发现这又是经典的问题，显然可以线段树加上可撤销并查集完成。

时间复杂度 $O(m\log m\log n)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
#define N 300010
using namespace std;
int fa[N],siz[N],tot;
int find(int x){return x==fa[x]?fa[x]:find(fa[x]);}
int chg[N],qtot;
void merge(int x,int y)
{
    int hx=find(x),hy=find(y);
    if(hx==hy) return;
    tot-=(siz[hx]&1)+(siz[hy]&1);
    if(siz[hx]>siz[hy]) swap(hx,hy);
    fa[hx]=hy;
    siz[hy]+=siz[hx];
    tot+=(siz[hy]&1);chg[++qtot]=hx;
}
void erase()
{
	int y=chg[qtot--],x=fa[y];
	tot-=siz[x]&1;
    siz[x]-=siz[y];fa[y]=y;
	tot+=(siz[x]&1)+(siz[y]&1);
}
struct road{
    int x,y,w,t;
    bool operator <(const road a)const{return w<a.w;}
}rd[N],rp[N];
int id[N],ans[N],ptot,n,m;
vector<road>ru[N<<2];
void insert(int u,int l,int r,int L,int R,road v)
{
    if(L>R) return;
    if(L<=l && r<=R){ru[u].push_back(v);return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
}
void solve(int u,int l,int r,int pre)
{
    if(l>r) return;
    int mid=(l+r)>>1,ut=qtot;
    for(road p:ru[u]) merge(p.x,p.y),pre=max(pre,p.w);
    if(l==r)
    {
		int cnt=0;
		while(tot && ptot<m)
        {
			road u=rp[++ptot];
			if(u.t<=l)
				merge(u.x,u.y),pre=max(pre,u.w),rd[++cnt]=u;
		}
		if(!tot)
        {
			for(int i=1;i<=cnt;i++) insert(1,1,m,rd[i].t,l-1,rd[i]);
			ans[l]=pre;
		}
		else ans[l]=-1;
	}
    else
    {
		int mid=(l+r)>>1;
        solve(u<<1|1,mid+1,r,pre);
        solve(u<<1,l,mid,pre);
	}
	while(qtot!=ut) erase();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&rd[i].x,&rd[i].y,&rd[i].w),rd[i].t=i;
        rp[i]=rd[i];
    }
    sort(rp+1,rp+m+1);
    tot=n;
    solve(1,1,m,-1);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
```
