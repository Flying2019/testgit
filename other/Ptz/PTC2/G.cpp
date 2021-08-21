#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 2010
#define db long double
#define inf 3e9
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
db w[N<<1];
void add(int u,int v,db w1)
{
    nxt[++cnt]=head[u];to[cnt]=v;
    w[cnt]=w1;head[u]=cnt;
}
queue<int>q;
int n,vis[N];
bool in[N];
db dis[N];
void clear()
{
    for(int i=0;i<=n;i++) in[i]=vis[i]=head[i]=0,dis[i]=inf;
    cnt=0;
    while(!q.empty()) q.pop();
}
bool spfa(int s)
{
    q.push(s);in[s]=true;vis[s]=1;
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        in[u]=false;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(dis[v]<=dis[u]+w[i]) continue;
            dis[v]=dis[u]+w[i];
            if(!in[v]) in[v]=true,q.push(v);
            if(++vis[v]>n+1) return false;
        }
    }
    return true;
}
int x[N],y[N],d[N],m;
db lim[N];
bool check(db X)
{
    clear();
    for(int i=1;i<=m;i++) add(y[i],x[i],X-d[i]);
    for(int i=1;i<=n;i++)
    {
        if(lim[i]!=-inf) add(0,i,lim[i]),add(i,0,-lim[i]);
        else add(0,i,1e6);
    }
    return spfa(0);
}
db read()
{
    int x=getchar(),s=0,f=1;
    for(;(x<'0' || x>'9') && x!='-' && x!='?';x=getchar());
    if(x=='?') return -inf;
    if(x=='-') f=-1,x=getchar();
    for(;x>='0' && x<='9';s=s*10+x-'0',x=getchar());
    return s*f;
}
int main()
{
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++) lim[i]=read();
        for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&d[i]);
        db l=0,r=inf,res=inf;
        while(r-l>1e-6)
        {
            db mid=(l+r)/2;
            if(check(mid)) r=mid,res=mid;
            else l=mid;
        }
        printf("%.6Lf\n",res);
        check(res);
        for(int i=1;i<=n;i++) printf("%.5Lf ",dis[i]);
        puts("");
    }
    return 0;
}