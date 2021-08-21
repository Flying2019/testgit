#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 410
#define M 1210
#define mod 998244353
using namespace std;
int nxt[M<<1],to[M<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
queue<int>q;
int n;
void make(int s,int dis[])
{
    for(int i=1;i<=n;i++) dis[i]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(!dis[v]) dis[v]=dis[u]+1;
        }
    }
}
int diss[N],dist[N];
int tot[N],di[N];
int answer(int s,int t)
{
    while(!q.empty()) q.pop();
    make(s,diss);
    make(t,dist);
    int p=diss[t];
    for(int i=1;i<=n;i++) di[i]=false;
    for(int i=1;i<=n;i++)
    if(diss[i]+dist[i]==p) q.push(i),tot[diss[i]]++;
    else if(diss[i]==dist[i]) return 0;
    for(int i=0;i<=p;i++)
    if(tot[i]>1) return 0;
    while(!q.empty())
    {
        int u=q.front();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(!di[v]) di[v]++,q.push(v);
        }
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++) printf("%d ",answer(i,j));
    return 0;
}