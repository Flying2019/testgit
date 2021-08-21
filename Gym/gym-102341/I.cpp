#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 400010
using namespace std;
vector<int>g[N];
int n,m,q;
namespace ST{
    int f[21][N*2],dep[N*2],id[N*2],tot;
    int _2[N*2],fa[N][21];
    void dfs(int u,int p)
    {
        dep[u]=dep[p]+1;fa[u][0]=p;
        for(int i=1;fa[u][i-1];i++) fa[u][i]=fa[fa[u][i-1]][i-1];
        f[0][++tot]=u;id[u]=tot;
        for(int v:g[u]) if(v!=p) dfs(v,u),f[0][++tot]=u;
    }
    int up(int x,int k)
    {
        for(int i=_2[dep[x]];i>=0;i--) if(k>>i&1) x=fa[x][i];
        return x;
    }
    int lca(int x,int y)
    {
        x=id[x],y=id[y];
        if(x>y) swap(x,y);
        int p=_2[y-x+1],u=1<<p;
        return dep[f[p][x]]>dep[f[p][y-u+1]]?f[p][y-u+1]:f[p][x];
    }
    void init()
    {
        dfs(1,0);
        for(int i=2;i<=tot;i++) _2[i]=_2[i>>1]+1;
        for(int i=1,p=2;p<=tot;i++,p<<=1)
            for(int j=1;j+p-1<=tot;j++)
            if(dep[f[i-1][j]]<dep[f[i-1][j+p/2]]) f[i][j]=f[i-1][j];
            else f[i][j]=f[i-1][j+p/2];
    }
}
using ST::dep;using ST::lca;
int dist(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
struct node{int u,v;node(int U=0,int V=-1):u(U),v(V){};}pre[N],suf[N],a[N];
node operator +(node a,node b)
{
    if(a.u==-1) return b;if(b.u==-1) return a;
    if(a.u==0 || b.u==0) return node();
    int d=dist(a.u,b.u),r=(a.v+b.v-d)/2;
    if(a.v>b.v+d) return b;if(b.v>a.v+d) return a;
    if((a.v+b.v-d)&1) throw;if(r<0) return node();
    int v=ST::up(b.u,b.v-r);
    if(!v || dist(a.u,v)!=a.v-r) v=ST::up(a.u,a.v-r);
    return node(v,r);
}
int ans[N];
namespace D{
    struct ques{
        int v,id,w;
    };
    vector<ques>q[N];
    bool cut[N];
    namespace Root{
        int siz[N],rt,mxr;
        void dfs(int u,int p){siz[u]=1;for(int v:g[u]) if(v!=p && !cut[v]) dfs(v,u),siz[u]+=siz[v];}
        void dfs2(int u,int p,int all)
        {
            int mx=all-siz[u];
            for(int v:g[u]) if(v!=p && !cut[v]) dfs2(v,u,all),mx=max(mx,siz[v]);
            if(!rt || mx<mxr) rt=u,mxr=mx;
        }
        int root(int u){dfs(u,0);rt=mxr=0;dfs2(u,0,siz[u]);return rt;}
    }
    void push(node u,int id,int w)
    {
        // printf("push %d %d %d\n",u.u,u.v,w*id);
        if(u.u<=0) return;
        q[u.u].push_back((ques){u.v,id,w});
    }
    int val[N];
    void add(int x,int v){++x;for(;x<=n;x+=(x&(-x))) val[x]+=v;}
    int qry(int x){++x;int v=0;for(;x;x-=(x&(-x))) v+=val[x];return v;}
    void dfs(int u,int p,int w,int d)
    {
        if(u<=m) add(d,w);
        for(int v:g[u]) if(v!=p && !cut[v]) dfs(v,u,w,d+1);
    }
    void answer(int u,int p,int d)
    {
        for(auto v:q[u]) if(v.v>=d) ans[v.id]+=qry(v.v-d)*v.w;
        for(int v:g[u]) if(v!=p && !cut[v]) answer(v,u,d+1);
    }
    void solve(int u)
    {
        u=Root::root(u);cut[u]=true;
        dfs(u,0,1,0);
        for(auto v:q[u]) ans[v.id]+=qry(v.v)*v.w;
        for(int v:g[u]) if(!cut[v]) dfs(v,u,-1,1),answer(v,u,1),dfs(v,u,1,1);
        dfs(u,0,-1,0);
        for(int v:g[u]) if(!cut[v]) solve(v);
    }
}
int main()
{
    scanf("%d",&n);m=n;
    for(int i=1,u,v;i<m;i++)
    {
        scanf("%d%d",&u,&v);++n;
        g[u].push_back(n),g[v].push_back(n);
        g[n].push_back(u),g[n].push_back(v);
    }
    ST::init();
    scanf("%d",&q);
    for(int t=1;t<=q;t++)
    {
        int k;scanf("%d",&k);
        for(int i=1;i<=k;i++) scanf("%d%d",&a[i].u,&a[i].v),a[i].v*=2;
        pre[0]=suf[k+1]=node(-1);
        for(int i=1;i<=k;i++)
            pre[i]=pre[i-1]+a[i];
        for(int i=k;i;i--)
            suf[i]=suf[i+1]+a[i];
        for(int i=1;i<=k;i++)
        if((pre[i-1]+suf[i+1]).u) D::push(pre[i-1]+suf[i+1],t,1),D::push(pre[k],t,-1);
        D::push(pre[k],t,1);
    }
    D::solve(1);
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}