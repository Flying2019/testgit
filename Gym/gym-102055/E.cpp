#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 100010
#define K 1010
#define ll long long
#define MP make_pair
#define fi first
#define se second
#define inf 100000000000000000ll
using namespace std;
int nxt[N<<2],to[N<<2],w[N<<2],head[N],cnt=1;
void add(int u,int v,int w0){nxt[++cnt]=head[u];w[cnt]=w0;to[cnt]=v;head[u]=cnt;}
struct road{
    int id;ll w;
    road(int X=0):id(X),w(::w[X]){}
    road(int X,ll Y):id(X),w(Y){}
    bool operator <(const road a)const{return w<a.w;}
};
bool vis[N],cir[N],cut[N<<2];int fa[N],fw[N];
int tt=0,att;
vector<road>a[N],a0;
vector<ll>f[N*2];vector<int> g[N*2];int px[N*2],py[N*2];
void dfs(int u,int p)
{
    fa[u]=p;vis[u]=true;
    for(int i=head[u];i;i=nxt[i])
    if(!cut[i])
    {
        cut[i]=cut[i^1]=true;
        int v=to[i];
        if(!vis[v]) fw[v]=i,dfs(v,u);
        else
        {
            ++tt;
            a[tt].push_back(i);
            for(int p=u;p!=v;p=fa[p])
                cir[p]=true,a[tt].push_back(fw[p]);
            sort(a[tt].begin(),a[tt].end());
            f[tt].resize(a[tt].size());
            f[tt][0]=a[tt][0].w;
            for(int j=1;j<a[tt].size();j++) f[tt][j]=f[tt][j-1]+a[tt][j].w;
            f[tt][0]=0;
        }
    }
}
struct node{
    int id,v;
    node(int I=0,int V=0):id(I),v(V){}
    bool operator <(const node a)const{return v>a.v;}
};
priority_queue<node>q;
void dfs_cut(int p,int k)
{
    if(!k) return;
    if(p<=att){for(int i=0;i<=k;i++) cut[a[p][i].id]=cut[a[p][i].id^1]=true;return;}
    int X=g[p][k];
    dfs_cut(px[p],X);dfs_cut(py[p],k-X);
}
int col[N],cl;
void dfs_col(int u)
{
    col[u]=cl;
    for(int i=head[u];i;i=nxt[i])
    if(!cut[i] && !col[to[i]]) dfs_col(to[i]);
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n,m,k;scanf("%d%d%d",&n,&m,&k);
        int k0=k;
        auto clear=[&]()
        {
            for(int i=1;i<=n;i++) head[i]=col[i]=cir[i]=vis[i]=fa[i]=fw[i]=0;
            for(int i=1;i<=cnt;i++) cut[i]=0;cnt=1;
            for(int i=1;i<=tt;i++) f[i].clear(),g[i].clear(),px[i]=py[i]=0;
            for(int i=1;i<=att;i++) a[i].clear();a0.clear();
            while(!q.empty()) q.pop();
            tt=att=0;cl=0;
        };
        for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
        for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i,0),--k;
        for(int i=1;i<=cnt;i++) cut[i]=false;
        if(k<0)
        {
            cl=1;
            for(int i=1;i<=n;i++)
                if(!col[i]) dfs_col(i),cl++;
            printf("Case %d: ",_);
            printf("%lld\n",0ll);
            for(int i=1;i<=n;i++) printf("%d ",min(col[i],k0));
            puts("");
            clear();
            continue;
        }
        int ct=0;
        att=tt;
        for(int i=1;i<=tt;i++) if(f[i].size()>k+1) f[i].resize(k+1);
        a0.push_back(0);
        for(int i=2;i<=n;i++) if(!cir[i] && fw[i]) a0.push_back(fw[i]),++ct;
        sort(a0.begin(),a0.end());
        for(int i=1;i<a0.size();i++) a0[i].w+=a0[i-1].w;
        for(int i=1;i<=tt;i++) q.push(node(i,f[i].size()));
        while(q.size()>1)
        {
            int x=q.top().id;q.pop();
            int y=q.top().id;q.pop();
            int p=min(k+1,(int)f[x].size()+(int)f[y].size()-1);
            ++tt;g[tt].resize(p);f[tt].resize(p);px[tt]=x;py[tt]=y;
            for(int i=0;i<p;i++) f[tt][i]=inf;
            for(int i=1;i<f[x].size();i++) if(f[tt][i]>f[x][i]) f[tt][i]=f[x][i],g[tt][i]=i;
            for(int i=1;i<f[y].size();i++) if(f[tt][i]>f[y][i]) f[tt][i]=f[y][i],g[tt][i]=0;
            for(int i=1;i<f[x].size();i++)
                for(int j=1;j<f[y].size() && i+j<p;j++)
                if(f[tt][i+j]>f[x][i]+f[y][j])
                {
                    f[tt][i+j]=f[x][i]+f[y][j];
                    g[tt][i+j]=i;
                }
            q.push(node(tt,f[tt].size()));
        }
        ll ans=inf;int id=0;
        if(ct>=k) ans=a0[k].w;
        for(int i=0;i<f[tt].size() && i<=k;i++)
        if(i+ct>=k && a0[k-i].w+f[tt][i]<ans) ans=a0[k-i].w+f[tt][i],id=i;
        for(int i=1;i<=k-id;i++) cut[a0[i].id]=cut[a0[i].id^1]=true;
        dfs_cut(tt,id);
        cl=1;
        for(int i=1;i<=n;i++)
            if(!col[i]) dfs_col(i),cl++;
        printf("Case %d: ",_);
        printf("%lld\n",ans);
        for(int i=1;i<=n;i++) printf("%d ",col[i]);
        puts("");
        clear();
    }
    return 0;
}