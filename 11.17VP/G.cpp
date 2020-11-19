#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
using namespace std;
typedef int typ;
#define M 1000010
#define inf 1000000000
#define winf 1000000000
struct road{
    int nxt,to,f;
    typ w;
}r[M<<1];
int head[N],cnt=1,all;
void add(int u,int v,int f,typ w)
{
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
namespace min_cost_flow{
    int cur[N];
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
}
int ss=1,tt=2,n,m,k,c,d;
vector<int>g[N];
inline int id(int t,int x){return t*n+x+2;}
void work(int t)
{
    all+=n;
    for(int u=1;u<=n;u++)
        for(int v:g[u])
        {
            for(int p=1;p<=k;p++)
            add(id(t,u),id(t+1,v),1,d*(2*p-1));
        }
    for(int u=1;u<=n;u++) add(id(t,u),id(t+1,u),inf,0);
    add(id(t+1,1),tt,inf,c*(t+1));
}
int main()
{
    scanf("%d%d%d%d%d",&n,&m,&k,&c,&d);
    all=n+2;
    for(int i=1;i<=k;i++)
    {
        int a;
        scanf("%d",&a);
        add(ss,id(0,a),1,0);
    }
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);g[v].push_back(u);
    }
    add(id(0,1),tt,inf,0);
    for(int i=0;i<=n+k;i++) work(i);
    min_cost_flow::work(ss,tt);
    printf("%d\n",min_cost_flow::minw);
    return 0;
}