#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 500010
using namespace std;
typedef long long ll;
#define M 1000010
#define inf 1000000000
#define winf 1000000000000000000
struct road{
    int nxt,to,f;
    ll w;
}r[M<<1];
int head[N],cnt=1;
void add(int u,int v,int f,ll w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
bool vis[N];
struct node{
    int u;ll v;
    node(int U=0,ll V=0):u(U),v(V){}
    bool operator <(const node a)const{return v<a.v;}
};
priority_queue<node>q;
ll dis[N],tag[N];
int pre[N],all;
void push(int s,int t)
{
    for(int i=0;i<=all;i++) tag[i]=dis[i];
    for(int i=t;i!=s;i=r[pre[i]^1].to) r[pre[i]].f--,r[pre[i]^1].f++;
}
// queue<int>q;
// void spfa(int s,int t)
// {
//     for(int i=0;i<=all;i++) dis[i]=winf;
// }
ll dij(int s,int t)
{
    for(int i=0;i<=all;i++) dis[i]=-winf;
    dis[s]=0;q.push(node(s,0));
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i;i=r[i].nxt)
        {
            int v=r[i].to;ll w=r[i].w-tag[v]+tag[u];
            if(r[i].f && dis[u]+w>dis[v]) dis[v]=dis[u]+w,q.push(node(v,dis[v])),pre[v]=i;
        }
    }
    for(int i=1;i<=all;i++) vis[i]=false;
    return dis[t];
}
int x[N],y[N];ll w[N];
int main()
{
    int n,m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%lld",&x[i],&y[i],&w[i]),m=max(m,y[i]);++m;
    int t=m,s=0;
    all=m;
    for(int i=0;i<m;i++) add(i,i+1,2,0);
    for(int i=1;i<=n;i++) add(x[i],y[i]+1,1,w[i]);
    ll res=0;
    for(int i=0;i<=all;i++) dis[i]=-winf;dis[0]=0;
    for(int u=0;u<=all;u++)
        for(int i=head[u];i;i=r[i].nxt)
        {
            int v=r[i].to;
            if(r[i].f && dis[v]<dis[u]+r[i].w) dis[v]=dis[u]+r[i].w,pre[v]=i;
        }
    push(s,t);res=dis[t];
    printf("%lld\n",res*2+dij(s,t));
    return 0;
}