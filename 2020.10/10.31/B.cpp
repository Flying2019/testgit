#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int dep[N],len[N],son[N],fa[N],k;
void dfs(int u)
{
    dep[u]=dep[fa[u]]+1;
    len[u]=1;son[u]=0;
    for(int i=head[u];i;i=nxt[i])
    {
        dfs(to[i]);
        if(len[to[i]]+1>len[u]) len[u]=len[to[i]]+1,son[u]=to[i];
    }
}
int arr[N<<4],par=1;
int* new_(int l){par+=l+1;return arr+(par-l);}
int *f[N],*g[N];
int sw[N];
void work(int u)
{
    if(son[u])
    {
        g[son[u]]=g[u]+1;f[son[u]]=f[u]+1;
        work(son[u]);
    }
    f[u][0]=(k>len[u]?0:g[u][max(k+1,1)])+1;
    g[u][0]=max(g[u][1],f[u][0]);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==son[u]) continue;
        f[v]=new_(len[v]+1),g[v]=new_(len[v]+1);
        work(v);
        int *pf=f[v]-1,*pg=g[v]-1;
        for(int l=0;l<=len[v];l++) sw[l]=f[u][l];
        for(int l=1;l<=len[v];l++)
        {
            int r=max(l,k-l+1);
            if(r<=len[u]) sw[l]=max(sw[l],pf[l]+g[u][r]);
        }
        for(int l=0;l<=len[v];l++)
        {
            int r=max(max(l,k-l+1),1);
            if(r<=len[v]) sw[l]=max(sw[l],f[u][l]+pg[r]);
        }
        for(int l=len[v];l>=0;l--) f[u][l]=sw[l],g[u][l]=max(f[u][l],g[u][l+1]);
    }
    // printf("%d:%d %d\n",u,f[u][0],g[u][0]);
}
int main()
{
    // freopen("independent.in","r",stdin);
    // freopen("independent.out","w",stdout);
    int n;
    scanf("%d%d",&n,&k);k--;
    for(int i=2;i<=n;i++) scanf("%d",&fa[i]),add(++fa[i],i);
    dfs(1);
    f[1]=new_(len[1]+1),g[1]=new_(len[1]+1);
    work(1);
    // printf("%d\n",par);
    // for(int i=1;i<=n;i++) printf("%d ",f[i]-arr);puts("");
    printf("%d\n",g[1][0]);
    return 0;
}