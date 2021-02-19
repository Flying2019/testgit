#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define ll long long
using namespace std;
int f[N],fa[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int a[N],b[N];//a:count of 0 , b:count of 1
ll g[N];
struct node{
    int u,a,b;
    bool operator <(const node v)const{return 1ll*a*v.b<1ll*v.a*b;}
};
bool vis[N];
priority_queue<node>q;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=2;i<=n;i++) scanf("%d",&fa[i]);
    for(int i=1;i<=n;i++)
    {
        int c;
        scanf("%d",&c);
        a[i]=!c,b[i]=c;
        if(i!=1) q.push((node){i,a[i],b[i]});
    }
    while(!q.empty())
    {
        int u=q.top().u,v=find(fa[u]);q.pop();
        if(vis[u]) continue;vis[u]=true;
        g[v]+=g[u]+1ll*b[v]*a[u];
        a[v]+=a[u],b[v]+=b[u],f[u]=v;
        if(v!=1) q.push((node){v,a[v],b[v]});
    }
    printf("%lld\n",g[1]);
    return 0;
}