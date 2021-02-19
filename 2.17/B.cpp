#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 250010
#define D 19
using namespace std;
int f[N][D],dep[N],n;
int val[N];
void add(int x,int v){for(;x<=n;x+=(x&(-x))) val[x]=max(val[x],v);}
int qry(int x){int r=0;for(;x;x-=(x&(-x))) r=max(r,val[x]);return r;}
int _2[N],a[N];
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=_2[dep[x]-dep[y]];i>=0;i--)
    if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=_2[dep[x]];i>=0;i--)
    if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
vector<int>v[N];
int ans[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) _2[i]=_2[i>>1]+1;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        int u=a[i],w=qry(u)+1;add(u,w);
        v[w].push_back(u);
        if(w==1){dep[u]=1;continue;}
        auto b=lower_bound(v[w-1].rbegin(),v[w-1].rend(),u);--b;
        int p=lca(v[w-1].back(),*b);
        dep[u]=dep[p]+1;f[u][0]=p;
        for(int i=1;f[u][i-1];i++) f[u][i]=f[f[u][i-1]][i-1];
    }
    for(int i=1;i<=n;i++) ans[i]+=dep[a[i]]-1;
    for(int i=1;i<=n;i++) val[i]=0,dep[i]=0,v[i].clear(),memset(f[i],0,sizeof(f[i]));
    for(int i=n;i;i--)
    {
        int u=a[i],w=qry(n-u+1)+1;add(n-u+1,w);
        v[w].push_back(u);
        if(w==1){dep[u]=1;continue;}
        int p=*lower_bound(v[w-1].begin(),v[w-1].end(),u);
        p=lca(v[w-1].back(),p);
        dep[u]=dep[p]+1;f[u][0]=p;
        for(int i=1;f[u][i-1];i++) f[u][i]=f[f[u][i-1]][i-1];
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]+dep[a[i]]-1);
    return 0;
}