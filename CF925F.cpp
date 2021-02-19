#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 1000000000000000ll
#define N 100010
#define ll long long
using namespace std;
namespace dinic{
    int nxt[N<<1],to[N<<1],head[N],cnt=1;ll w[N<<1];
    int all;
    int adde(int u,int v,ll w1){nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=w1;head[u]=cnt;return cnt;}
    int add(int u,int v,ll w){int p=adde(u,v,w);adde(v,u,0);return p;}
    int dep[N],cur[N];queue<int>q;
    bool bfs(int s,int t)
    {
        for(int i=1;i<=all;i++) dep[i]=0,cur[i]=head[i];
        dep[s]=1;q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=head[u];i;i=nxt[i])
            if(w[i] && !dep[to[i]]) dep[to[i]]=dep[u]+1,q.push(to[i]);
        }
        return dep[t];
    }
    ll dfs(int u,int t,ll flow=inf)
    {
        if(u==t || !flow) return flow;ll r=0;
        for(int &i=cur[u];i;i=nxt[i])
        {
            int v=to[i];ll f;
            if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,w[i])))) w[i]-=f,w[i^1]+=f,flow-=f,r+=f;
        }
        return r;
    }
    ll work(int s=all-1,int t=all){int r=0;while(bfs(s,t)) r+=dfs(s,t);return r;}
    void reset(){for(int i=2;i<=cnt;i+=2) w[i]+=w[i^1],w[i^1]=0;}
}
using dinic::add;
int n,m,ids[N],idu[N],idt[N],a[N],b[N],c[N],d[N];
const int M=100000000;
int solve(int t)
{
    dinic::reset();
    ll s=0;
    for(int i=1;i<=m;i++)
    {
        dinic::w[ids[i]]=1ll*t*a[i]+1ll*M*b[i];
        dinic::w[idu[i]]=1ll*t*(c[i]-a[i])+1ll*M*(d[i]-b[i]);
        dinic::w[idt[i]]=1ll*t*a[i]+1ll*M*b[i];
        s+=1ll*t*a[i]+1ll*M*b[i];
    }
    return s-dinic::work();
}
int main()
{
    scanf("%d%d",&n,&m);
    int s=n+1,t=n+2;dinic::all=t;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d%d%d%d%d",&u,&v,&a[i],&b[i],&c[i],&d[i]);
        ids[i]=add(s,v,0);idu[i]=add(u,v,0);idt[i]=add(u,t,0);
    }
    int l=0,r=M;
    while(l+1<r)
    {
        int mid=(l+r)>>1;
        if(solve(mid-1)>solve(mid)) l=mid;
        else r=mid;
    }
    int L=l;r=M;
    while(l+1<r)
    {
        int mid=(l+r)>>1;
        if(solve(mid-1)) r=mid;
        else l=mid;
    }
    printf("%.7f",1.0*(r-L)/M);
    return 0;
}