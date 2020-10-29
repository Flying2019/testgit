#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
    nxt[++cnt]=head[v];
    to[cnt]=u;
    head[v]=cnt;
}
int f[N],vis[N],tvis,n;
int link[N],pre[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int lca(int x,int y)
{
    tvis++;
    for(x=find(x),y=find(y);vis[x]!=tvis;)
    {
        vis[x]=tvis;
        x=find(pre[link[x]]);
        if(y) swap(x,y);
    }
    return x;
}
int col[N];
queue<int>q;
void merge(int x,int y,int v)
{
    for(;find(x)!=v;x=pre[y])
    {
        pre[x]=y;
        y=link[x];
        if(col[y]==2) col[y]=1,q.push(y);
        if(x==find(x)) f[x]=v;
        if(y==find(y)) f[y]=v;
    }
}
bool check(int s)
{
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++) col[i]=pre[i]=0,f[i]=i;
    col[s]=1;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(find(u)==find(v) || col[v]==2) continue;
            if(!col[v])
            {
                col[v]=2;pre[v]=u;
                if(!link[v])
                {
                    for(int x=v,y;x;x=y) y=link[pre[x]],link[x]=pre[x],link[pre[x]]=x;
                    return true;
                }
                else col[link[v]]=1,q.push(link[v]);
            }
            else{int w=lca(u,v);merge(u,v,w),merge(v,u,w);}
        }
    }
    return false;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        memset(link,0,sizeof(link));
        memset(head,0,sizeof(head));
        memset(vis,0,sizeof(vis));
        cnt=tvis=0;
        int n,m,e;
        scanf("%d%d%d",&n,&m,&e);
        for(int i=1;i<=m;i++) add(i*3,i*3-1),add(i*3-1,i*3-2),add(i*3,i*3-2);
        for(int i=1;i<=e;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(x+m*3,y*3);add(x+m*3,y*3-1);add(x+m*3,y*3-2);
        }
        ::n=n+m*3;
        int ans=0;
        for(int i=::n;i>=1;i--)
        if(!link[i]) ans+=check(i);
        printf("%d\n",ans-n);
        for(int i=1;i<=n;i++) printf("%d ",(link[i+m*3]+2)/3);
        puts("");
    }
    return 0;
}