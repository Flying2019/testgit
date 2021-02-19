#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 55
#define M N*N*4
using namespace std;
char mp[N][N];
int L[N][N],R[N][N],U[N][N],D[N][N],n,m;
inline int id(int x,int y){return (x-1)*m+y;}
int nxt[M<<2],to[M<<2],head[M],cnt;
void add(int u,int v){nxt[++cnt]=head[u];to[cnt]=v;head[u]=cnt;}
int low[M],dfn[M],tot;
int st[M],tp,uid[M],val[M];
bool in[M];
void tarjan(int u)
{
    low[u]=dfn[u]=++tot;
    st[++tp]=u;in[u]=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(in[v]) low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        while(1)
        {
            int v=st[tp--];
            in[v]=false,uid[v]=u;
            if(v==u) break;
            val[u]+=val[v];
        }
    }
}
vector<int>g[M];
int f[M];
int dfs(int u)
{
    if(~f[u]) return f[u];
    f[u]=0;
    for(int v:g[u]) f[u]=max(f[u],dfs(v));
    f[u]+=val[u];
    return f[u];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    int X=0,Y=0,V=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]=='O') X=i,Y=j;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]=='#') continue;
        else L[i][j]=!L[i][j-1]?j:L[i][j-1];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
        if(mp[i][j]=='#') continue;
        else R[i][j]=!R[i][j+1]?j:R[i][j+1];
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++)
        if(mp[i][j]=='#') continue;
        else U[i][j]=!U[i-1][j]?i:U[i-1][j];
    for(int j=1;j<=m;j++)
        for(int i=n;i>=1;i--)
        if(mp[i][j]=='#') continue;
        else D[i][j]=!D[i+1][j]?i:D[i+1][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        if(mp[i][j]!='#')
        {
            if(L[i][j]!=j) add(id(i,j),id(i,L[i][j]));
            if(R[i][j]!=j) add(id(i,j),id(i,R[i][j]));
            if(U[i][j]!=i) add(id(i,j),id(U[i][j],j));
            if(D[i][j]!=i) add(id(i,j),id(D[i][j],j));
        }
    memset(f,-1,sizeof(f));
    for(int i=1;i<=n*m;i++)
    if(!dfn[i]) tarjan(i);
    for(int u=1;u<=n*m;u++)
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(uid[u]!=uid[v]) g[uid[u]].push_back(uid[v]);
        }
    int res=dfs(uid[id(X,Y)]);
    printf("%d\n",res);
    puts(res==V?"YES":"NO");
    return 0;
}