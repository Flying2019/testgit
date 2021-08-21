#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt=1;
int deg[N],x[N],y[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];to[cnt]=v;head[u]=cnt;
    nxt[++cnt]=head[v];to[cnt]=u;head[v]=cnt;
    deg[u]++;deg[v]++;
}
bool vis[N<<1];
int ton[N],tt;
int q[N*2],ql=N+1,qr=N;
int fl[N];
void dfs(int u)
{
    for(int &i=head[u];i;i=nxt[i])
    if(!vis[i])
    {
        int v=to[i];
        vis[i]=vis[i^1]=true;
        int w=i;
        dfs(v);ton[++tt]=w;
    }
}
int st[N];
int main()
{
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    ++m;
    for(int i=1;i<=n;i++)
    {
        int op;scanf("%d%d",&op,&x[i]);
        if(op==1) add(x[i],m),y[i]=m;
        else if(op==2) scanf("%d",&y[i]),add(x[i],y[i]);
    }
    int tot=0;
    for(int i=1;i<=m;i++)
    if(deg[i]&1) ++tot;
    int id=0;
    if(tot>2) throw;
    if(tot==2)
        for(int i=1;i<m;i++) if(deg[i]&1){add(i,m),id=cnt-1;break;}
    dfs(m);
    // for(int i=1;i<=tt;i++)
    // {
    //     int x0=x[ton[i]/2],y0=y[ton[i]/2];
    //     if(!(ton[i]&1)) swap(x0,y0);
    //     cerr<<x0<<" -> "<<y0<<endl;
    // }
    if(id)
    {
        int u=1;
        for(int i=1;i<=tt;i++) if(ton[i]==id || ton[i]==(id^1)){u=i;break;}
        int pt=0;
        for(int i=u+1;i<=tt;i++)
        {
            if(!(ton[i]&1) && y[ton[i]/2]==m) pt=0;
            if(pt)
            {
                q[++qr]=ton[i]/2;
                if(!(ton[i]&1)) fl[ton[i]/2]=true;
            }
            else
            {
                q[--ql]=ton[i]/2;
                if(ton[i]&1) fl[ton[i]/2]=true;
            }
            pt=!pt;
        }
        for(int i=u-1;i;i--)
        {
            if(ton[i]&1 && y[ton[i]/2]==m) pt=0;
            if(pt)
            {
                q[++qr]=ton[i]/2;
                if(ton[i]&1) fl[ton[i]/2]=true;
            }
            else
            {
                q[--ql]=ton[i]/2;
                if(!(ton[i]&1)) fl[ton[i]/2]=true;
            }
            pt=!pt;
        }
        for(int u=1;u<m;u++)
        if(head[u])
        {
            for(int i=head[u];i;i=nxt[i])
            if(!vis[i])
            {
                vis[i]=vis[i^1]=true;
                int v=to[i];
                if(st[v])
                {
                    q[st[v]]=i/2;
                    if(!(i&1)) fl[i/2]=true;
                    st[v]=0;
                }
                else
                {
                    q[--ql]=i/2;
                    if(i&1) fl[i/2]=true;
                    ++qr;st[v]=qr;
                }
            }
            for(int i=head[u];i;i=nxt[i]) if(st[to[i]]) st[to[i]]=0;
        }
    }
    if(!id)
    {
        for(int u=1;u<=m;u++)
        {
            int c=0;
            for(int i=head[u];i;i=nxt[i])
            if(!vis[i] && to[i]==u) c++;
            if((c/2)&1)
            {
                for(int i=head[u];i;i=nxt[i])
                if(!vis[i] && to[i]==u)
                {
                    vis[i]=vis[i^1]=true;
                    q[++qr]=i/2;break;
                }
                break;
            }
        }
        for(int u=1;u<m;u++)
        if(head[u])
        {
            for(int i=head[u];i;i=nxt[i])
            if(!vis[i])
            {
                vis[i]=vis[i^1]=true;
                int v=to[i];
                if(st[v])
                {
                    q[st[v]]=i/2;
                    if(!(i&1)) fl[i/2]=true;
                    st[v]=0;
                }
                else
                {
                    q[--ql]=i/2;
                    if(i&1) fl[i/2]=true;
                    ++qr;st[v]=qr;
                }
            }
            for(int i=head[u];i;i=nxt[i]) if(st[to[i]]) st[to[i]]=0;
        }
        // for(int i=ql;i<=qr;i++) cerr<<q[i]<<" ";cerr<<endl;
        // for(int i=ql;i<=qr;i++)
        // {
        //     if(y[q[i]]==m) cerr<<x[q[i]]<<" ";
        //     else if(fl[q[i]]) cerr<<y[q[i]]<<" "<<x[q[i]]<<" ";
        //     else cerr<<x[q[i]]<<" "<<y[q[i]]<<" ";
        // }
        // cerr<<endl;
        int pt=0;
        for(int i=1;i<=tt;i++)
        {
            if(!(ton[i]&1) && y[ton[i]/2]==m) pt=0;
            if(pt)
            {
                q[++qr]=ton[i]/2;
                if(!(ton[i]&1)) fl[ton[i]/2]=true;
            }
            else
            {
                q[--ql]=ton[i]/2;
                if(ton[i]&1) fl[ton[i]/2]=true;
            }
            pt=!pt;
        }
    }
    for(int i=ql;i<=qr;i++) printf("%d ",q[i]);puts("");
    for(int i=ql;i<=qr;i++) printf("%d ",fl[q[i]]);puts("");
    return 0;
}