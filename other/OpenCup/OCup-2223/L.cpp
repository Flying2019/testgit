#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
#define M N*2.5
#define ll long long
using namespace std;
int f[N],s[N];ll res;
ll calc(int x){return 1ll*x*(x-1)/2;}
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
void merge(int x,int y)
{
    x=find(x),y=find(y);
    if(x==y) return;
    if(s[x]>s[y]) swap(x,y);
    res-=calc(s[x])+calc(s[y]);
    f[x]=y,s[y]+=s[x];
    res+=calc(s[y]);
}
struct road{
    int x,y,t;
};
vector<int>rts,g[N];
int dfn[N],low[N],tt;
int ton[N],tp;
bool in[N];
void dfs(int u)
{
    dfn[u]=low[u]=++tt;
    ton[++tp]=u;in[u]=true;
    for(int v:g[u])
    if(!dfn[v]) dfs(v),low[u]=min(low[u],low[v]);
    else if(in[v]) low[u]=min(low[u],dfn[v]);
    if(dfn[u]==low[u])
    {
        for(int p=ton[tp--];p!=u;p=ton[tp--]) merge(u,p),in[p]=false;
        in[u]=false;
    }
}
void adde(int x,int y){g[x].push_back(y);rts.push_back(x);rts.push_back(y);}
void work(vector<road>&v)
{
    for(road t:v) adde(find(t.x),find(t.y));
    for(int u:rts) if(!dfn[u]) dfs(u);
    for(int u:rts) dfn[u]=low[u]=in[u]=0,g[u].clear();
    tt=0;rts.clear();
}
int ftmp[N],stmp[N];
void split(vector<road> v,int tl,vector<road>&vl,vector<road>&vr)
{
    for(road &t:v) if(t.t<=tl) adde(t.x=find(t.x),t.y=find(t.y));
    for(int u:rts) ftmp[u]=f[u],stmp[u]=s[u];
    ll rtmp=res;
    for(int u:rts) if(!dfn[u]) dfs(u);
    for(road t:v)
    if(t.t>tl || find(t.x)!=find(t.y)) vr.push_back(t);
    else vl.push_back(t);
    for(int u:rts) dfn[u]=low[u]=in[u]=0,g[u].clear(),f[u]=ftmp[u],s[u]=stmp[u];
    tt=0;
    res=rtmp;rts.clear();
}
void solve(int l,int r,vector<road>&v)
{
    int m=(l+r)>>1;
    if(l==r){work(v);printf("%lld\n",res);return;}
    vector<road>vl,vr;
    split(v,m,vl,vr);
    solve(l,m,vl);solve(m+1,r,vr);
}
vector<road>rd;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    rd.resize(m);
    for(int i=0;i<m;i++) scanf("%d%d",&rd[i].x,&rd[i].y),rd[i].t=i;
    for(int i=1;i<=n;i++) f[i]=i,s[i]=1;
    solve(0,m-1,rd);
    return 0;
}