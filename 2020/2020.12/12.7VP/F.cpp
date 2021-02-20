#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define N 5010
#define M 100010
#define P pair<ll,ll>
#define MP make_pair
#define fi first
#define se second
#define inf 1000000000000ll
#define winf 1000000000000000ll
struct road{
    int nxt,to;
    ll f,w;
}r[M<<1];
int head[N],cnt=1,all;
void add(int u,int v,ll f,ll w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
vector<P >res,ans;
namespace min_cost_flow{
    int cur[N];
    bool vis[N];
    struct node{
        int u;ll v;
        node(int U=0,ll V=0):u(U),v(V){}
        bool operator <(const node a)const{return v>a.v;}
    };
    priority_queue<node>q;
    ll dis[N],tag[N];
    bool dij(int s,int t)
    {
        for(int i=1;i<=all;i++) dis[i]=winf,cur[i]=head[i];
        dis[t]=0;q.push(node(t,0));
        while(!q.empty())
        {
            int u=q.top().u;q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(int i=head[u];i;i=r[i].nxt)
            {
                int v=r[i].to;ll w=tag[u]+r[i^1].w-tag[v];
                if(r[i^1].f && dis[u]+w<dis[v]) dis[v]=dis[u]+w,q.push(node(v,dis[v]));
            }
        }
        for(int i=1;i<=all;i++) tag[i]=min(tag[i]+dis[i],winf);
        if(!vis[s]) return false;
        for(int i=1;i<=all;i++) vis[i]=false;
        return true;
    }
    ll dfs(int u,int t,ll fl)
    {
        if(u==t || !fl) return fl;
        ll res=0;
        vis[u]=true;
        for(int &i=cur[u];i;i=r[i].nxt)
        if(r[i].f)
        {
            int v=r[i].to;ll f;
            if(!vis[v] && tag[v]+r[i].w==tag[u] && (f=dfs(v,t,min(fl,r[i].f))))
            {
                r[i].f-=f,r[i^1].f+=f;
                res+=f,fl-=f;
                if(!fl) break;
            }
        }
        vis[u]=false;
        return res;
    }
    void work(int s,int t)
    {
        ll minw=0,maxf=0;
        while(dij(s,t))
        {
            ll w=dfs(s,t,inf);
            res.push_back(MP(tag[s],w));
            ans.push_back(MP(maxf,minw));
            maxf+=w,minw+=w*tag[s];
            if(w>5e8) return;
        }
    }
}
struct node{
    ll s,p,c;
    bool operator< (const node a)const{return s<a.s;}
}a[60][60];int c[60];
int id[60][60];
int main()
{
    int n;
    scanf("%d",&n);
    int s=1,t=2;all=2;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c[i]);
        for(int j=1;j<=c[i];j++) scanf("%lld%lld%lld",&a[i][j].s,&a[i][j].p,&a[i][j].c);
        sort(a[i]+1,a[i]+c[i]+1);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=c[i]-1;j++) id[i][j]=++all;
        id[i][0]=s,id[i][c[i]]=t;
        for(int j=1;j<=c[i];j++) add(id[i][j-1],id[i][j],a[i][j].p,0),add(id[i][j-1],id[i][j],inf,a[i][j].c);
    }
    int m;
    scanf("%d",&m);
    while(m --> 0)
    {
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        int k=1;
        for(int i=1;i<=c[v];i++)
        {
            while(k<=c[u] && a[u][k].s+w<a[v][i].s) k++;
            add(id[v][i-1],id[u][k-1],inf,0);
        }
    }
    min_cost_flow::work(s,t);
    int q;
    scanf("%d",&q);
    while(q --> 0)
    {
        ll v;
        scanf("%lld",&v);
        int p=lower_bound(res.begin(),res.end(),MP(v,-winf))-res.begin();
        if(p==res.size()) puts("-1");
        else printf("%lld\n",ans[p].fi*v-ans[p].se);
    }
    return 0;
}