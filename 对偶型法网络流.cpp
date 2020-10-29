#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
typedef long long typ;
#define N 30010
#define inf 1000000000
#define winf 10000000000000ll
struct road{
    int nxt,to,f;
    typ w;
}r[N<<2];
int head[N],cnt=1;
void add(int u,int v,int f,typ w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
int cur[N],all;
bool vis[N];
struct node{
    int u;typ v;
    node(int U=0,typ V=0):u(U),v(V){}
    bool operator <(const node a)const{return v>a.v;}
};
priority_queue<node>q;
typ dis[N],tag[N];
bool dij(int s,int t)
{
    for(int i=1;i<=all;i++) dis[i]=winf,cur[i]=head[i];
    dis[t]=0;q.push(node(t,0));
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i;i=r[i].nxt)
        {
            int v=r[i].to,w=tag[u]+r[i^1].w-tag[v];
            if(r[i^1].f && dis[u]+w<dis[v]) dis[v]=dis[u]+w,q.push(node(v,dis[v]));
        }
    }
    for(int i=1;i<=all;i++) tag[i]=min(tag[i]+dis[i],winf);
    if(!vis[s]) return false;
    for(int i=1;i<=all;i++) vis[i]=false;
    return true;
}
int dfs(int u,int t,int fl)
{
    if(u==t || !fl) return fl;
    int res=0;
    vis[u]=true;
    for(int &i=cur[u];i;i=r[i].nxt)
    if(r[i].f)
    {
        int v=r[i].to,f;
        if(!vis[v] && tag[v]+r[i].w==tag[u] && (f=dfs(v,t,min(fl,r[i].f))))
        {
            r[i].f-=f,r[i^1].f+=f;
            res+=f,fl-=f;
            if(!fl) break;
        }
    }
    vis[u]=false;
    return res;
}
int maxf;typ minw;
void work(int s,int t){while(dij(s,t)){int w=dfs(s,t,inf);maxf+=w,minw+=w*tag[s];}}
int main()
{
    int n,m,s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);all=n;
    for(int i=1;i<=m;i++)
    {
        int u,v,w,f;
        scanf("%d%d%d%d",&u,&v,&f,&w);
        add(u,v,f,w);
    }
    work(s,t);
    printf("%d %d\n",maxf,minw);
    return 0;
}