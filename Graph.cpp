#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
#define M 100010
using namespace std;
int nxt[M<<1],to[M<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;
    deg[v]++;
    head[u]=cnt;
}
priority_queue<int,vector<int>,greater<int> >q1;
priority_queue<int>q2;
int ax[N],ay[N],ac;
int tp[N],tt;
int main()
{
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for(int i=1;i<=n;i++)
    if(!deg[i]) q1.push(i);
    while(!q1.empty() || !q2.empty())
    {
        if(!q1.empty())
        {
            int x=q1.top();q1.pop();
            if(!k || (q1.empty() && (q2.empty() || x>q2.top())))
            {
                for(int i=head[x];i;i=nxt[i])
                {
                    int v=to[i];
                    --deg[v];if(!deg[v]) q1.push(v);
                }
                tp[++tt]=x;
            }
            else k--,q2.push(x);
        }
        else
        {
            int x=q2.top();q2.pop();
            ax[++ac]=tp[tt],ay[ac]=x;
            for(int i=head[x];i;i=nxt[i])
            {
                int v=to[i];
                --deg[v];if(!deg[v]) q1.push(v);
            }
            tp[++tt]=x;
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",tp[i]);puts("");
    printf("%d\n",ac);
    for(int i=1;i<=ac;i++) printf("%d %d\n",ax[i],ay[i]);
    return 0;
}