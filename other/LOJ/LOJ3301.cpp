#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define N 4010
#define inf 1000000000000000000ll
#define ull unsigned long long
#define ll long long
using namespace std;
namespace dinic{
    int all;
    #define M 200010
    struct road{
        int nxt,to;ll w;
    }r[M];
    int head[N],cnt;
    void add(int u,int v,ll w)
    {
        r[++cnt]=(road){head[u],v,w};head[u]=cnt;
        r[++cnt]=(road){head[v],u,0};head[v]=cnt;
    }
    int dis[N],cur[N];
    queue<int>q;
    bool bfs(int s,int t)
    {
        for(int i=1;i<=all;i++) dis[i]=0,cur[i]=head[i];
        dis[s]=1;q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=head[u];i;i=r[i].nxt)
            if(r[i].w)
            {
                int v=r[i].to;
                if(!dis[v]) dis[v]=dis[u]+1,q.push(v);
            }
        }
        return dis[t];
    }
    ll dfs(int u,int t,ll flow=inf)
    {
        if(u==t || !flow) return flow;
        ll res=0;
        for(int &i=cur[u];i;i=r[i].nxt)
        {
            int v=r[i].to;ll f;
            if(dis[v]==dis[u]+1 && (f=dfs(v,t,min(flow,r[i].w))))
            {
                flow-=f;res+=f;
                r[i].w-=f;r[i^1].w+=f;
                if(!flow) break;
            }
        }
        return res;
    }
    ll work(int s,int t){ll res=0;while(bfs(s,t)) res+=dfs(s,t);return res;}
    void init(int n)
    {
        for(int i=1;i<=n;i++) head[i]=cur[i]=0;cnt=1;
        all=n;
    }
    #undef M
}
using dinic::add;
using dinic::work;
using dinic::init;
#define M 63
ull va[M+3],vb[M+3];
ull insert(ull x,ull v=0)
{
    for(int i=M;~i;i--)
    if((x>>i)&1)
    {
        if(!va[i]){va[i]=x,vb[i]=v;return 0;}
        x^=va[i],v^=vb[i];
    }
    return v;
}
vector<int>g[N];
ull c[N];int a[N],b[N],w[N];
int l[N],r[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int mx=0;
    for(int i=1;i<=n;i++) scanf("%llu",&c[i]);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]),mx=max(mx,w[i]);
    for(int i=0;i<m;i++) scanf("%d",&a[i]);
    for(int i=0;i<m;i++) scanf("%d",&b[i]);
    for(int i=0;i<m;i++) insert(c[a[i]],1ull<<i);
    for(int i=1;i<=n;i++)
    {
        ull s=insert(c[i]);
        for(int j=0;j<m;j++) if(s>>j&1) g[a[j]].push_back(i);
    }
    memset(va,0,sizeof(va));memset(vb,0,sizeof(vb));
    for(int i=0;i<m;i++) insert(c[b[i]],1ull<<i);
    for(int i=1;i<=n;i++)
    {
        ull s=insert(c[i]);
        for(int j=0;j<m;j++) if(s>>j&1) g[i].push_back(b[j]);
    }
    // for(int i=1;i<=n;i++,puts(""))
    //     for(int v:g[i]) printf("%d ",v);
    for(int i=1;i<=n;i++) r[i]=mx;
    int s=n+1,t=n+2;
    ll ans=0;
    for(int _=0;_<=20;_++)
    {
        dinic::init(t);
        for(int i=1;i<=n;i++) add(s,i,1ll*(w[i]-l[i])*(w[i]-l[i]));
        for(int i=1;i<=n;i++) add(i,t,1ll*(w[i]-r[i])*(w[i]-r[i]));
        for(int u=1;u<=n;u++)
            for(int v:g[u])
            if(l[u]==l[v] && r[u]==r[v]) add(u,v,inf);
        ans=dinic::work(s,t);
        // printf("~ %lld\n",ans);
        for(int i=1;i<=n;i++)
        if(dinic::dis[i]) l[i]=(l[i]+r[i])>>1;
        else r[i]=(l[i]+r[i])>>1;
    }
    printf("%lld\n",ans);
    return 0;
}