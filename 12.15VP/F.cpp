#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define N 60
#define M N*6
#define inf 100000000
using namespace std;
int nxt[M<<1],to[M<<1],cnt;
void add(int head[],int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int h1[N],h2[N],deg[N],in[N];
vector<int>g[N];
int f1[N],f2[N],n;
void dfs(int u,int f[],int head[],int p=0)
{
    f[u]=p;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,f,head,u);
    }
}
queue<int>q;
inline bool diff(int x){return f1[x]!=f2[x];}
int solve()
{
    int c=0;
    for(int i=1;i<=n;i++)
    if(diff(i)) c++;
    else if(diff(f1[i])) return inf;
    for(int i=1;i<=n;i++) g[i].clear(),in[i]=0;
    for(int i=1;i<=n;i++)
    if(diff(i))
    {
        if(diff(f1[i])) g[i].push_back(f1[i]),in[f1[i]]++;
        if(diff(f2[i])) g[f2[i]].push_back(i),in[i]++;
    }
    for(int i=1;i<=n;i++)
    if(diff(i) && !in[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int v:g[u])
        {
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
    if(diff(i) && in[i]) return inf;
    return c;
}
void clear()
{
    memset(h1,0,sizeof(h1));memset(h2,0,sizeof(h2));
    cnt=0;memset(deg,0,sizeof(deg));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        clear();
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(h1,u,v),add(h1,v,u);++deg[u],++deg[v];
        }
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            add(h2,u,v),add(h2,v,u);
        }
        dfs(1,f1,h1);dfs(1,f2,h2);
        bool can=true;
        for(int i=1;i<=n;i++)
        if(f1[i]!=f2[i]) can=false;
        if(can){puts("0");continue;}
        int ans=inf;
        for(int i=1;i<=n;i++)
        if(deg[i]==1)
        {
            dfs(i,f2,h2);
            for(int j=1;j<=n;j++)
            if(i!=j)
            {
                dfs(j,f1,h1);f1[j]=i;f1[i]=0;
                ans=min(ans,solve()+1);
            }
        }
        printf("%d\n",ans>n?-1:ans);
    }
    return 0;
}