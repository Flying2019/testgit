#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#define ll long long
using namespace std;
int nxt[N<<1],to[N<<1],w[N<<1],head[N],cnt;
void add(int u,int v,int w1)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=w1;
    head[u]=cnt;
}
#define inf 1e9
struct node{
    ll x;
    int c;
    node(ll X=0,int C=0):x(X),c(C){}
    node operator +(node a){return node(x+a.x,c+a.c);}
    bool operator <(const node a)const{return x<a.x || (x==a.x && c>a.c);}
}f[N][3];//0:no 1:one 2:full
void dfs(int u,int p,ll x)
{
    f[u][0]=f[u][1]=node(0,0);f[u][2]=node(x,1);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u,x);
       	f[u][2]=max(f[u][2]+f[v][0],f[u][1]+f[v][1]+node(w[i]+x,1));
       	f[u][1]=max(f[u][0]+f[v][1]+node(w[i],0),f[u][1]+f[v][0]);
       	f[u][0]=f[u][0]+f[v][0];
    }
    f[u][0]=max(f[u][0],max(f[u][1]+node(x,1),f[u][2]));
}
int main()
{
    // freopen("lct1.in","r",stdin);
    int n,k;
    scanf("%d%d",&n,&k);++k;
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    ll l=-inf,r=inf,res=0;
    while(r>=l)
    {
        ll mid=(l+r)>>1;
        dfs(1,0,mid);
        if(f[1][0].c<=k) l=mid+1,res=f[1][0].x-k*mid;
        else r=mid-1;
    }
    printf("%lld\n",res);
    return 0;
}