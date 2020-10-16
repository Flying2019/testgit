### [链接](http://acm.hdu.edu.cn/showproblem.php?pid=4725)
### 题目大意
给定 $n$ 个点的无向图，每个点有一个层数 $c_i$，如果两个点的层数相差1，那么这两个点之间有一条长度为 $C$ 的边。

除此之外还有 $m$ 条额外边，求 $1\rightarrow n$ 的最短路。
### 题解
显然是最短路，但是直接连边显然会挂。

不妨考虑一个套路：既然所有边都是 $C$，我们不妨规定一个节点 $u+n$ 表示 $u$ 这一层的所有进来的边，长度为 $C$。然后该点向所有 $u$ 层的点连一条长度为0的边。表示入边。

注意这些都是单向的。这样就防止同一层内的点互相转移。

直接跑最短路即可。复杂度 $O(m\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define M 800010
#define ll long long
using namespace std;
int nxt[M],to[M],w[M],head[N],cnt;
void add(int u,int v,int w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
struct node{
    int u;
    ll w;
    node(int U=0,int W=0):u(U),w(W){}
    bool operator <(const node a)const{return w>a.w;}
};
ll dis[N];
bool vis[N];
priority_queue<node>q;
ll dij(int s,int t)
{
    memset(dis,60,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    q.push(node(s,dis[s]));
    while(!q.empty())
    {
        int u=q.top().u;
        q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(!vis[v] && dis[v]>dis[u]+w[i])
            {
                dis[v]=dis[u]+w[i];
                q.push(node(v,dis[v]));
            }
        }
    }
    return dis[t];
}
int have[N],l[N];
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        memset(have,0,sizeof(have));
        memset(head,0,sizeof(head));
        cnt=0;
        int n,m,c;
        scanf("%d%d%d",&n,&m,&c);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&l[i]);
            have[l[i]]++;
        }
        for(int i=1;i<=n;i++)
        {
            add(n+l[i],i,0);
            if(have[l[i]+1]) add(i,n+l[i]+1,c);
            if(have[l[i]-1]) add(i,n+l[i]-1,c);
        }
        for(int i=1;i<=m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);add(v,u,w);
        }
        ll res=dij(1,n);
        printf("Case #%d: %lld\n",_,res>=1e12?-1:res);
    }

    return 0;
}
```
