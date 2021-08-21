#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int a[N];char s[N];
int f[N],siz[N];
int dfs(int u,int p)
{
    siz[u]=a[u];f[u]=0;
    int mx=0,mw=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        int w=dfs(v,u);siz[u]+=siz[v];
        f[u]+=f[v]+siz[v];
        if(!mx || f[v]>f[mx]) mx=v,mw=w;
    }
    if(!mx) return 0;
    return max(f[u]&1,(mw+siz[mx])-(f[u]-f[mx]-siz[mx]));
}
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) a[i]=s[i]=='1';
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    int ans=n*n;
    for(int i=1;i<=n;i++)
        if(!dfs(i,0)) ans=min(ans,f[i]);
    printf("%d\n",ans>=n*n?-1:ans/2);
    return 0;
}