#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1010
#define M 10010
#define inf 1e9
using namespace std;
struct node{
    int to,nxt,f,w;
}r[M];
int head[N],cnt=1;
void add(int u,int v,int f,int w)
{
    r[++cnt]=(node){v,head[u],f,w},head[u]=cnt;
    r[++cnt]=(node){u,head[v],0,-w},head[v]=cnt;
}
int dis[N],fl[N],pre[N],bef[N];
int all;
bool in[N];
queue<int>q;
bool spfa(int s,int t)
{
    for(int i=1;i<=all;i++) dis[i]=-inf,fl[i]=inf,in[i]=false;
    dis[s]=0;
    pre[t]=-1;in[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in[u]=false;
        for(int i=head[u];i;i=r[i].nxt)
        if(r[i].f)
        {
            int v=r[i].to;
            if(dis[v]<dis[u]+r[i].w)
            {
                dis[v]=dis[u]+r[i].w;
                fl[v]=min(fl[u],r[i].f);
                pre[v]=u;
                bef[v]=i;
                if(!in[v]) in[v]=true,q.push(v);
            }
        }
    }
    return pre[t]!=-1;
}
int MCMF(int s,int t)
{
    int mf=0;int mc=0;
    while(spfa(s,t))
    {
        mf+=fl[t],mc+=fl[t]*dis[t];
        for(int u=t;u!=s;u=pre[u])
        r[bef[u]].f-=fl[t],r[bef[u]^1].f+=fl[t];
    }
    return mc;
}
void clear(){memset(head,0,sizeof(head));cnt=1;}
double p;
struct plane{
    int x,l,r;
}pl[N];
int su[N*2],pn[N*2];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        clear();
        int n,a,b,tn=0;
        scanf("%d%d%d%lf",&n,&a,&b,&p);
        for(int i=1;i<=n;i++) scanf("%d%d%d",&pl[i].x,&pl[i].l,&pl[i].r),pn[++tn]=pl[i].l,pn[++tn]=--pl[i].r;pn[++tn]=1e9+5;
        sort(pn+1,pn+tn+1);
        tn=unique(pn+1,pn+tn+1)-pn-1;
        for(int i=1;i<=n;i++) pl[i].l=lower_bound(pn+1,pn+tn+1,pl[i].l)-pn,pl[i].r=lower_bound(pn+1,pn+tn+1,pl[i].r)-pn;
        for(int i=1;i<=tn;i++) su[i]=0;
        for(int i=1;i<=n;i++) su[pl[i].l]++,su[pl[i].r+1]--;
        for(int i=1;i<=tn;i++) su[i]+=su[i-1];
        if(*max_element(su+1,su+tn+1)>a+b){puts("impossible");continue;}
        int s=tn+n+1,t=tn;all=s;
        int ans=0;
        add(s,1,a,0);
        for(int i=1;i<tn;i++) add(i,i+1,1e8,0);
        for(int i=1;i<=n;i++)
        {
            ans+=pl[i].x;
            add(pl[i].l,tn+i,1,pl[i].x-(int)(pl[i].x*p+0.0001));
            add(tn+i,pl[i].l+1,1,0);
            add(tn+i,pl[i].r+1,1,(int)(pl[i].x*p+0.0001));
        }
        printf("%d\n",ans-MCMF(s,t));
    }
    return 0;
}