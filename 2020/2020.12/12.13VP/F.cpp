#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 2010
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}
int x[N],y[N];
int fa[N][N];
queue<P >q;
int r[N][N];
void push(int u,int x,int s)
{
    if(u!=s && r[x][u]){q.push(MP(s,u));return;}
    r[x][u]=s;
    for(int i=head[u];i;i=nxt[i])
    if(to[i]!=fa[x][u]) push(to[i],x,s);
}
void make(int u,int s){for(int i=head[u];i;i=nxt[i]) if(to[i]!=fa[s][u]) fa[s][to[i]]=u,make(to[i],s);}
void adds(int x,int y)
{
    q.push(MP(x,y));
    while(!q.empty())
    {
        int x=q.front().fi,y=q.front().se;q.pop();
        int &e1=r[x][y],&e2=r[y][x];
        if(e1==y) continue;
        if(e1) q.push(MP(e1,y));
        else if(e2) q.push(MP(e2,x));
        else e1=y,e2=x,push(y,x,y),push(x,y,x);
    }
}
int qry(int u,int s,int p)
{
    int ans=0;
    if(u!=p && r[p][u]) ans=1,p=u;
    for(int i=head[u];i;i=nxt[i])
    if(to[i]!=fa[s][u]) ans+=qry(to[i],s,p);
    return ans;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;i++) make(i,i);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        adds(x,y);
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans+=qry(i,i,i);
    printf("%d\n",ans/2);
    return 0;
}