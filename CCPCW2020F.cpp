#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;deg[v]++;
    head[u]=cnt;
}
int n,m;
int cl[N],vis[N],res[N],ra,id[N],ans[N],fa;
int q[N],ql,qr;
vector<int>g[N];
void check(int s,int t)
{
    memset(cl,-1,sizeof(int)*(n+2));
    memset(id,0,sizeof(int)*(n+2));
    memset(res,0,sizeof(int)*(n+2));
    ql=1,qr=0;q[++qr]=s;q[++qr]=t;cl[s]=1;cl[t]=0;
    while(ql<=qr)
    {
        int u=q[ql++];
        for(int i=head[u];i;i=nxt[i])
        if(cl[to[i]]==-1) cl[to[i]]=cl[u],q[++qr]=to[i];
    }
    int tt=0,mt=0;
    for(int i=1;i<=n;i++)
    if(cl[i]==1)
    {
        res[id[i]=++tt]=i;mt+=deg[i];
    }mt-=tt;ra=n/tt;
    if(ra<fa || n%tt!=0 || mt&1 || ra*mt/2+(ra-1)*tt!=m) return;
    for(int p=0;p<ra-1;p++)
    {
        int *f=res+p*tt,c=0;
        for(int q=1;q<=tt;q++)
        {
            int u=f[q];
            for(int i=head[u];i;i=nxt[i])
            {
                int v=to[i];
                if(id[v]) continue;
                if(f[q+tt]) return;
                id[v]=id[u]+tt;f[q+tt]=v;++c;
            }
        }
        if(c!=tt) return;
    }
    for(int i=1;i<=n;i++) g[i].clear();
    for(int p=0;p<ra;p++)
    {
        int *f=res+p*tt;
        for(int q=1;q<=tt;q++)
        {
            int u=f[q];
            for(int i=head[u];i;i=nxt[i])
            {
                int v=to[i];
                if((id[v]-1)/tt==(id[u]-1)/tt)
                    g[id[v]].push_back((id[u]-1)%tt+1);
            }
        }
    }
    for(int i=tt+1;i<=n;i++)
    if(g[i]!=g[i-tt]) return;
    fa=ra;
    memcpy(ans,res,sizeof(int)*(n+2));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    int u=1;
    for(int i=2;i<=n;i++)
    if(deg[i]<deg[u]) u=i;
    for(int i=1;i<=n;i++) ans[i]=i;fa=1;
    if(m<=1ll*n*(n/2-1)/2+n/2) for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        check(u,v);
    }
    printf("%d %d\n",fa,n/fa);
    for(int i=1;i<=n;i++)
    {
        printf("%d ",ans[i]);
        if(i%(n/fa)==0) puts("");
    }
    return 0;
}