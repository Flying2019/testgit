#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 100000000
#define N 410
#define M 200010
using namespace std;
int a[N][N];
int x[M],y[M],n,m;
int dy[M],id[M],b[N][N];
namespace flow{
    int nxt[M<<1],from[M<<1],to[M<<1],w[M<<1],head[M],cnt=1;
    int cur[M],all;
    int add(int u,int v,int w1)
    {
        nxt[++cnt]=head[u];to[cnt]=v;from[cnt]=u;w[cnt]=w1;head[u]=cnt;
        nxt[++cnt]=head[v];to[cnt]=u;from[cnt]=v;w[cnt]=0;head[v]=cnt;
        return cnt;
    }
    int dep[M];
    queue<int>q;
    bool bfs(int s,int t)
    {
        for(int i=1;i<=all;i++) dep[i]=inf,cur[i]=head[i];
        dep[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];i;i=nxt[i])
            if(w[i]){
                int v=to[i];
                if(dep[v]>=inf)
                dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]<inf;
    }
    int dfs(int u,int t,int fl)
    {
        if(u==t || !fl) return fl;
        int res=0;
        for(int &i=cur[u];i;i=nxt[i])
        {
            int v=to[i],f;
            if(dep[v]==dep[u]+1 && (f=dfs(v,t,min(fl,w[i]))))
            {
                w[i]-=f;
                w[i^1]+=f;
                fl-=f;
                res+=f;
                if(!fl) break;
            }
        }
        return res;
    }
    void dinic(int s,int t,int ty)
    {
        for(int i=2;i<=cnt;i+=2)
        if(!w[i])
        {
            if(from[i]==s || to[i]==t) w[i]=1,w[i^1]=0;
            else w[i]=w[i^1]=0;
        }
        while(bfs(s,t)) dfs(s,t,inf);
        for(int i=1;i<=n*m;i++)
        if(w[id[i]]) dy[i]=ty;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    bool flag=false;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) x[a[i][j]]=i,y[a[i][j]]=j;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) id[(i-1)*m+j]=flow::add(x[(i-1)*m+j],i+n,1);
    int s=n*2+1,t=s+1;flow::all=t;
    for(int i=1;i<=n;i++) flow::add(s,i,1),flow::add(i+n,t,1);
    for(int i=1;i<=m;i++) flow::dinic(s,t,i);

    for(int i=1;i<=n*m;i++) b[x[i]][dy[i]]=i;
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=m;j++) printf("%d ",b[i][j]);
    for(int i=1;i<=n*m;i++) b[(i-1)/m+1][dy[i]]=i;
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=m;j++) printf("%d ",b[i][j]);
    return 0;
}