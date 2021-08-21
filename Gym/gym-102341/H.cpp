#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define N 200010
#define db double
using namespace std;
bool vis[N];
db dis[N],mn[N],p[N];
vector<int>g[N];
struct node{
    int u;db v;
    bool operator <(const node a)const{return v>a.v;}
};
priority_queue<node>q;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) dis[i]=mn[i]=1e10;
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    dis[n]=mn[n]=0;q.push((node){n,0});
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int v:g[u])
        if(!vis[v] && dis[u]-mn[v]<2.0/3)
        {
            if(dis[u]<mn[v]) p[v]=1,mn[v]=dis[u],dis[v]=mn[v]+1.5;
            else p[v]*=0.25, dis[v]+=(dis[u]-mn[v]-2.0/3)*p[v]*0.75;
            q.push((node){v,dis[v]});
        }
    }
    printf("%.10lf",dis[1]);
    return 0;
}