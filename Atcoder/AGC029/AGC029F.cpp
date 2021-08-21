#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 200010
#define M 800010
#define inf 100000000
using namespace std;
int nxt[M<<1],to[M<<1],w[M<<1],head[N],cnt=1;
void add(int u,int v,int f)
{
    nxt[++cnt]=head[u];to[cnt]=v;
    w[cnt]=f;head[u]=cnt;
}
void adde(int u,int v,int w1=inf,int w2=0){add(u,v,w1);add(v,u,w2);}
int all,dep[N],cur[N];
queue<int>q;
bool bfs(int s,int t)
{
    for(int i=1;i<=all;i++) dep[i]=0,cur[i]=head[i];
    q.push(s);dep[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        if(w[i] && !dep[to[i]]) dep[to[i]]=dep[u]+1,q.push(to[i]);
    }
    return dep[t];
}
int dfs(int u,int t,int flow=inf)
{
    if(u==t || !flow) return flow;
    int res=0;
    for(int &i=cur[u];i;i=nxt[i])
    {
        int v=to[i],f;
        if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(flow,w[i]))))
        {
            flow-=f,res+=f;
            w[i]-=f,w[i^1]+=f;
            if(!flow) break;
        }
    }
    return res;
}
int dinic(int s,int t){int res=0;while(bfs(s,t)) res+=dfs(s,t);return res;}
int s,t;
int id[N],ax[N],ay[N],tt;
void dfs(int u)
{
    ++tt;
    for(int i=head[u];i;i=nxt[i])
    if(w[i])
    {
        int v=to[i];
        if(v==s || id[v]) continue;
        id[v]=u;
        for(int j=head[v];j;j=nxt[j])
        if(w[j])
        {
            ax[v]=u,ay[v]=to[j];
            dfs(to[j]);
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);s=2*n,t=s+1;all=t;
    for(int i=1;i<=n;i++) adde(s,i,1);
    for(int i=1;i<n;i++) adde(i+n,t,1);
    for(int i=1;i<n;i++)
    {
        int c,a;
        scanf("%d",&c);
        while(c --> 0) scanf("%d",&a),adde(a,i+n,1);
    }
    if(dinic(s,t)!=n-1){puts("-1");return 0;}
    for(int i=head[s];i;i=nxt[i])
    if(w[i]){dfs(to[i]);break;}
    if(tt!=n){puts("-1");return 0;}
    for(int i=n+1;i<n*2;i++) printf("%d %d\n",ax[i],ay[i]);
    return 0;
}