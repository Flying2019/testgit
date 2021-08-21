#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
#define pb push_back
#define mod 993244853
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
int dfn[N],low[N],tt;
int q[N],qt,idn;
vector<int>g[N];
void tarjan(int u)
{
    dfn[u]=low[u]=++tt;
    q[++qt]=u;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])
            {
                if(q[qt]==v){g[u].pb(v),g[v].pb(u);qt--;continue;}
                int t;++idn;
                g[u].pb(idn);g[idn].pb(u);
                do{
                    t=q[qt--];
                    g[t].pb(idn);g[idn].pb(t);
                }while(t!=v);
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
}
int n;
int f[N][2];//0:未匹配 1:已匹配
void dfs(int u,int p)
{
    if(u<=n)
    {
        f[u][0]=1;
        for(int v:g[u])
        if(v!=p)
        {
            dfs(v,u);
            f[u][1]=(1ll*f[u][1]*f[v][1]-1ll*f[u][0]*f[v][0]%mod+mod)%mod;
            f[u][0]=1ll*f[u][0]*f[v][1]%mod;
        }
    }
    else
    {
        vector<int>h;
        for(int v:g[u])
            if(v!=p) dfs(v,u);
        int w0=1,w1=1;
        {
            int i=0;
            for(;i<g[u].size();i++) if(g[u][i]==p) break;
            for(i++;i<g[u].size();i++) h.push_back(g[u][i]);
            for(int v:g[u]) if(v!=p) h.push_back(v); else break;
        }
        for(int v:h) w0=1ll*w0*f[v][0]%mod;
        f[u][0]=(g[u].size()&1?mod-2ll:2ll)*w0%mod;
        w0=0,w1=1;
        for(int v:h)
        {
            int g0=w0,g1=w1;
            w1=(1ll*g1*f[v][1]-1ll*g0*f[v][0]%mod+mod)%mod,w0=1ll*g1*f[v][0]%mod;
        }
        f[u][0]=(f[u][0]+w0)%mod;f[u][1]=(f[u][1]+w1)%mod;
        w0=mod-1,w1=0;
        for(int v:h)
        {
            int g0=w0,g1=w1;
            w1=(1ll*g1*f[v][1]-1ll*g0*f[v][0]%mod+mod)%mod,w0=1ll*g1*f[v][0]%mod;
        }
        f[u][0]=(f[u][0]+w1)%mod;
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    idn=n;
    tarjan(1);
    // puts("");
    // for(int u=1;u<=idn;u++) for(int v:g[u]) printf("%d %d\n",u,v);
    dfs(1,0);
    printf("%d\n",f[1][1]);
    return 0;
}