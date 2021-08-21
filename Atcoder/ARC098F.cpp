#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 100010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
int f[N],a[N],c[N];
ll g[N],h[N],b[N];
bool vis[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
bool cmp(int x,int y){return c[x]<c[y];}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%lld",&a[i],&b[i]),c[i]=max(a[i]-b[i],0ll),f[i]=h[i]=i,g[i]=c[i];
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    sort(h+1,h+n+1,cmp);
    for(int p=1;p<=n;p++)
    {
        int u=h[p];vis[u]=true;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i],w=find(v);
            if(!vis[v] || w==u) continue;
            b[u]+=b[w], g[u]=min(g[u],max(g[w],c[u]-b[w]));
            f[w]=u;
        }
    }
    printf("%lld\n",g[find(1)]+b[find(1)]);
    return 0;
}