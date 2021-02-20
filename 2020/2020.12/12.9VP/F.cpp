#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define M 500010
using namespace std;
int nxt[M<<1],to[M<<1],w[M<<1],head[N],cnt=1;
int all;
namespace Dinic{
    #define inf 100000000
    queue<int>q;
    bool in[N];
    int dep[N],cur[N];
    bool bfs(int s,int t)
    {
        for(int i=1;i<=all;i++) dep[i]=0,cur[i]=head[i];
        q.push(s);
        dep[s]=1;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=head[u];i;i=nxt[i])
            if(w[i])
            {
                int v=to[i];
                if(!dep[v]) dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t];
    }
    int dfs(int u,int t,int flow)
    {
        if(!flow || u==t) return flow;
        int r=0;
        for(int &i=cur[u];i;i=nxt[i])
        if(w[i])
        {
            int v=to[i],f;
            if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,w[i]))))
            {
                flow-=f,r+=f;
                w[i]-=f,w[i^1]+=f;
                if(!flow) break;
            }
        }
        return r;
    }
    int dinic(int s,int t){int r=0;while(bfs(s,t)) r+=dfs(s,t,inf);return r;}
}
void add(int u,int v,int w1)
{
    nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=w1;
    head[u]=cnt;
    nxt[++cnt]=head[v];to[cnt]=u;w[cnt]=0;
    head[v]=cnt;
}
int p[N],q[N];
int pi[N],qi[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]),p[i]++;
    for(int i=1;i<=n;i++) scanf("%d",&q[i]),q[i]++;
    for(int i=1;i<=n;i++) pi[i]=i,qi[i]=i+n;
    for(int i=1;i<=n;i++)
    if(pi[i]==i) for(int u=p[i];u!=i;u=p[u]) pi[u]=i;
    for(int i=1;i<=n;i++)
    if(qi[i]==i+n) for(int u=q[i];u!=i;u=q[u]) qi[u]=i+n;
    int s=n*2+1,t=s+1,c=0;all=t;
    for(int i=1;i<=n;i++)
    if(p[i]!=i && q[i]!=i)
    {
        add(qi[i],pi[i],1);
        if(p[i]==q[i]) add(pi[i],qi[i],1);
    }
    else if(p[i]==i && q[i]==i) ++c;
    else if(p[i]==i) add(qi[i],t,1);
    else add(s,pi[i],1);
    printf("%d\n",n-Dinic::dinic(s,t)-c);
    return 0;
}