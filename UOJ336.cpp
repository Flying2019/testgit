#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<cstring>
using namespace std;
typedef long long typ;
#define inf 1000000000
#define N 30010
#define M 100010
#define winf 10000000000000ll
struct road{
    int nxt,to,f;
    typ w;
}r[M<<1];
int head[N],cnt=1;
bool rev=0;
void add(int u,int v,int f,typ w)
{
    if(rev) swap(u,v);
    r[++cnt]=(road){head[u],v,f,w};head[u]=cnt;
    r[++cnt]=(road){head[v],u,0,-w};head[v]=cnt;
}
namespace min_cost_flow{
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
}
#define get(x,y,z) (((x-1)*m+y-1)*4+z)
#define U get(i,j,1)
#define R get(i,j,2)
#define D get(i,j,3)
#define L get(i,j,4)
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int s=n*m*4+1,t=s+1,res=0;
    min_cost_flow::all=t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            rev=(i+j+1)%2;
            int o=rev?t:s;
            if((i+j)&1)
            {
                if(i-1>=1) add(U,get(i-1,j,3),1,0);
                if(i+1<=n) add(D,get(i+1,j,1),1,0);
                if(j-1>=1) add(L,get(i,j-1,2),1,0);
                if(j+1<=m) add(R,get(i,j+1,4),1,0);
            }
            if(x&1) add(o,U,1,0),res++;
            if(x&2) add(o,R,1,0),res++;
            if(x&4) add(o,D,1,0),res++;
            if(x&8) add(o,L,1,0),res++;
            if(x==1) add(U,L,1,1),add(U,R,1,1),add(U,D,1,2);
            if(x==2) add(R,U,1,1),add(R,D,1,1),add(R,L,1,2);
            if(x==4) add(D,L,1,1),add(D,R,1,1),add(D,U,1,2);
            if(x==8) add(L,U,1,1),add(L,D,1,1),add(L,R,1,2);

            if(x==3) add(U,D,1,1),add(R,L,1,1);
            if(x==6) add(D,U,1,1),add(R,L,1,1);
            if(x==9) add(U,D,1,1),add(L,R,1,1);
            if(x==12)add(D,U,1,1),add(L,R,1,1);

            if(x==7) add(U,L,1,1),add(D,L,1,1),add(R,L,1,2);
            if(x==11)add(L,D,1,1),add(R,D,1,1),add(U,D,1,2);
            if(x==13)add(U,R,1,1),add(D,R,1,1),add(L,R,1,2);
            if(x==14)add(L,U,1,1),add(R,U,1,1),add(D,U,1,2);
        }
    min_cost_flow::work(s,t);
    printf("%d",2*min_cost_flow::maxf==res?min_cost_flow::minw:-1);
    return 0;
}