#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 4010
#define M 100010
#define ll long long
using namespace std;
int all;
struct road{
    int nxt,to,f;
    ll w;
}r[M];
int head[N],cnt=1;
int add(int u,int v,int f,ll w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
    return cnt;
}
namespace max_cost_flow{
    #define inf 1000000000
    #define winf 10000000000000ll
    ll tag[N],dis[N];
    int cur[N];
    bool vis[N];
    struct node{
        int u;ll v;
        node(int U=0,ll V=0):u(U),v(V){}
        bool operator <(const node a)const{return v<a.v;}
    };
    priority_queue<node>q;
    queue<int>q0;
    bool spfa(int s,int t)
    {
        for(int i=1;i<=all;i++) dis[i]=-winf,cur[i]=head[i];
        dis[t]=0;q0.push(t);
        while(!q0.empty())
        {
            int u=q0.front();q0.pop();
            for(int i=head[u];i;i=r[i].nxt)
            {
                int v=r[i].to;ll w=r[i^1].w;
                if(r[i^1].f && dis[v]<dis[u]+w) dis[v]=dis[u]+w,q0.push(v);
            }
        }
        for(int i=1;i<=all;i++) tag[i]=max(tag[i]+dis[i],-winf);
        return dis[s]>-winf;
    }
    bool dij(int s,int t)
    {
        for(int i=1;i<=all;i++) dis[i]=-winf,cur[i]=head[i];
        dis[t]=0;q.push(node(t,dis[t]));
        while(!q.empty())
        {
            int u=q.top().u;q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(int i=head[u];i;i=r[i].nxt)
            {
                int v=r[i].to;ll w=r[i^1].w+tag[u]-tag[v];
                if(r[i^1].f && dis[v]<dis[u]+w) dis[v]=dis[u]+w,q.push(node(v,dis[v]));
            }
        }
        for(int i=1;i<=all;i++) tag[i]=max(tag[i]+dis[i],-winf),vis[i]=false;
        return dis[s]>-winf;
    }
    int dfs(int u,int t,int fl)
    {
        if(u==t || !fl) return fl;
        vis[u]=true;
        int res=0;
        for(int &i=cur[u];i;i=r[i].nxt)
        {
            int v=r[i].to,f;
            if(tag[v]+r[i].w==tag[u] && !vis[v] && (f=dfs(v,t,min(fl,r[i].f))))
            {
                r[i].f-=f; r[i^1].f+=f;
                fl-=f; res+=f;
                if(!fl) break;
            }
        }
        vis[u]=false;
        return res;
    }
    int maxf;ll maxw;
    void MCMF(int s,int t)
    {
        if(spfa(s,t)){int w=dfs(s,t,inf);maxf+=w;maxw+=1ll*w*tag[s];}
        else return;
        while(dij(s,t))
        {
            int w=dfs(s,t,inf);
            maxf+=w;maxw+=1ll*w*tag[s];
        }
    }
}
int a[N],b[N];
int id[N];
int main()
{
    // freopen("delight.in","r",stdin);
    // freopen("delight.out","w",stdout);
    int n,k,m1,m2;
    scanf("%d%d%d%d",&n,&k,&m1,&m2);
    m2=k-m2;
    ll res=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]),res+=b[i];
    int d=m2-m1;
    int s=n+2,t=s+1,o=n+1;all=t;
    add(s,o,m2,0);
    for(int i=1;i<=k;i++) add(o,i,inf,0);
    for(int i=1;i<n;i++) add(i,i+1,d,0);
    add(n,t,d,0);
    for(int i=1;i<=n;i++) id[i]=add(i,(i+k>n)?t:i+k,1,a[i]-b[i]);
    max_cost_flow::MCMF(s,t);
    printf("%lld\n",res+max_cost_flow::maxw);
    for(int i=1;i<=n;i++) putchar(r[id[i]].f?'S':'E');
    return 0;
}