#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long ll;
#define N 30010
#define M 100010
#define inf 100000000000000ll
using namespace std;
struct road{
    int nxt,to,f;
    ll w;
}r[M<<1];
int head[N],cnt=1;
void add(int u,int v,int f,ll w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
int all=0;
ll dis[N];int pre[N],bef[N];bool in[N];
queue<int>q;
bool spfa(int s,int t)
{
    for(int i=1;i<=all;i++) dis[i]=inf,pre[i]=0;
    q.push(s);dis[s]=0;
    in[s]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        in[u]=false;
        for(int i=head[u];i;i=r[i].nxt)
        if(r[i].f)
        {
            int v=r[i].to;
            if(dis[v]<=dis[u]+r[i].w) continue;
            dis[v]=dis[u]+r[i].w;
            pre[v]=u;bef[v]=i;
            if(!in[v]) q.push(v),in[v]=true;
        }
    }
    return pre[t];
}
ll MCMF(int s,int t)
{
    ll res=0;
    while(spfa(s,t))
    {
        int w=100000000;
        for(int u=t;u!=s;u=pre[u]) w=min(w,r[bef[u]].f);
        res+=1ll*w*dis[t];
        for(int u=t;u!=s;u=pre[u]) r[bef[u]].f-=w,r[bef[u]^1].f+=w;
    }
    return res;
}
int main()
{
    int n;
    scanf("%d",&n);
    int o1=n*2+1,o2=o1+1,o3=o2+1,o4=o3+1;
    int s=o4+1,t=s+1;all=t;
    for(int i=1;i<=n;i++)
    {
        int x,y,w;scanf("%d%d%d",&x,&y,&w);
        add(s,i,w,0);
        add(i,o1,w,x+y);add(i,o2,w,x-y);add(i,o3,w,-x+y);add(i,o4,w,-x-y);
    }
    for(int i=1;i<=n;i++)
    {
        int x,y,w;scanf("%d%d%d",&x,&y,&w);
        add(i+n,t,w,0);
        add(o1,i+n,w,-x-y);add(o2,i+n,w,-x+y);add(o3,i+n,w,x-y);add(o4,i+n,w,x+y);
    }
    printf("%lld",-MCMF(s,t));
    return 0;
}