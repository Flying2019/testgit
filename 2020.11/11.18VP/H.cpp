#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define ll long long
using namespace std;
typedef int typ;
#define N 50010
#define M 200010
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
int n;ll k[N],b[N],T;
#define X(a) (k[a]*T+b[a])
bool cmp1(int x,int y){return b[x]==b[y]?k[x]>k[y]:b[x]<b[y];}
bool cmp2(int x,int y){return X(x)==X(y)?x>y:X(x)<X(y);}
ll p1[N],p2[N],p[N];
bool check()
{
    ll mx=0;
    for(int i=1;i<=2*n;i++) p1[i]=p2[i]=i;
    sort(p1+1,p1+2*n+1,cmp1),sort(p2+n+1,p2+2*n+1,cmp2);
    for(int i=1;i<=2*n;i++)
    {
        mx=max(mx,X(p1[i]));
        if(p1[i]<=n) p[p1[i]]=mx;
    }
    sort(p+1,p+n+1);
    for(int i=n;i>=1;i--) if(p[i]<X(p2[i+n])) return false;
    return true;
}
inline int id(int x,int op){return (x<<1)-op;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) scanf("%lld%lld",&k[i],&b[i]);
    ll l=0,r=1000000002;
    while(l<r)
    {
        T=(l+r)>>1;
        if(check()) r=T;
        else T=l=T+1;
    }
    if(T>=1e9){puts("-1");return 0;}
    else printf("%d ",T);
    int s=n*4+1,t=s+1;all=t;
    for(int i=1;i<=2*n;i++)
    {
        if(i<=n) add(s,id(i,0),1,0);
        else add(id(i,1),t,1,0);
        add(id(i,0),id(i,1),inf,0);
    }
    for(int i=1;i<=2*n;i++) p1[i]=p2[i]=i;
    sort(p1+1,p1+2*n+1,cmp1);sort(p2+1,p2+2*n+1,cmp2);
    int pre=id(p1[1],0);
	for(int i=2;i<=2*n;i++)
    {
        int u=++all;
        add(u,pre,inf,0);
        add(u,id(p1[i],0),inf,0);
        add(id(p1[i],0),pre,inf,1);
        pre=u;
    }
    pre=id(p2[1],1);
	for(int i=2;i<=2*n;i++)
    {
        int u=++all;
        add(u,pre,inf,0);
        add(u,id(p2[i],1),inf,0);
        add(id(p2[i],1),pre,inf,1);
        pre=u;
    }
    min_cost_flow::work(s,t);
    printf("%lld\n",min_cost_flow::minw);
    return 0;
}