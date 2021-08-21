#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
#define S(a) ((int)a.size())
#define pb push_back
#define For01(x) for(int x=0;x<=1;x++)
using namespace std;
typedef long long ll;
typedef vector<ll> vec;
const ll inf=10000000000000000;
vec max(const vec &a,const vec &b)
{
    vec c=S(a)>S(b)?a:b;
    for(int i=0;i<min(S(a),S(b));i++) c[i]=max(a[i],b[i]);
    return c;
}
vec operator +(const vec &a,const vec &b)
{
    if(!S(a) || !S(b)) return vec();
    vec c;c.reserve(S(a)+S(b));
    c.push_back(a[0]+b[0]);
    int p=1,q=1;ll w=a[0]+b[0];
    while(p<S(a) || q<S(b))
    {
        if(q>=S(b) || (p<S(a) && a[p]-a[p-1]>b[q]-b[q-1])) c.push_back(w+=a[p]-a[p-1]),p++;
        else c.push_back(w+=b[q]-b[q-1]),q++;
    }
    return c;
}
vec inc(vec a,int k,int w=0)
{
    vec b(S(a)+k,-inf);for(ll v:a) b[k++]=v+w;return b;
}
int nxt[N<<1],to[N<<1],head[N],w[N<<1],cnt;
void add(int u,int v,int l){nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=l;head[u]=cnt;}
vec f[N][2];//端点 u 是否强制不匹配 (f[u][0]>=f[u][1])
int son[N],siz[N],fa[N],fw[N];
void dfs1(int u,int p)
{
    fa[u]=p;siz[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        fw[v]=w[i];
        dfs1(v,u);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
struct matr{
    vec g[2][2];//g[0/1][0/1]：左边/右边 是否强制不匹配
    //g[0][x]>=g[1][x] , g[x][0]>=g[x][1]
    vec* operator [](int a){return g[a];}
    matr(){}
    matr(int u){g[0][0]=f[u][0];g[0][1]=g[1][0]=f[u][1];}
};
matr merge(const matr &a,const matr &b,int w)
{
    matr c;
    For01(X) For01(x) For01(y) For01(Y)
    if(x && y) c[X][Y]=max(c[X][Y],inc(a.g[X][x]+b.g[y][Y],1,w));
    else c[X][Y]=max(c[X][Y],a.g[X][x]+b.g[y][Y]);
    return c;
}
matr solve(int l,int r,vec &g)
{
    if(l==r) return matr(g[l]);
    int s=0,mid=l;
    for(int i=l;i<=r;i++) s+=f[g[i]][0].size();
    int w=f[g[l]][0].size();
    while(mid<r-1 && w*2<=s) w+=f[g[++mid]][0].size();
    return merge(solve(l,mid,g),solve(mid+1,r,g),fw[g[mid]]);
}
vec g[N];
void dfs2(int u,int top)
{
    f[u][0].pb(0);f[u][1].pb(0);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==son[u] || v==fa[u]) continue;
        dfs2(v,v);
    }
    if(u==1) return;
    if(son[u]) dfs2(son[u],top);
    g[top].push_back(u);
    if(u!=top) return;
    auto s=solve(0,S(g[top])-1,g[top]);
    int p=fa[u];
    f[p][0]=max(f[p][0]+s[0][0],inc(f[p][1]+s[0][1],1,fw[u]));
    f[p][1]=f[p][1]+s[0][0];
    g[top].clear();f[u][0].clear();f[u][1].clear();
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    dfs1(1,0);
    son[1]=0;
    dfs2(1,1);
    for(int i=1;i<n;i++)
    if(i>=S(f[1][0])) printf("? ");
    else printf("%lld ",f[1][0][i]);
    return 0;
}