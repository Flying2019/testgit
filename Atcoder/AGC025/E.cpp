#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 4010
#define fi first
#define se second
#define MP make_pair
using namespace std;
typedef pair<int,int> P;
int x[N],y[N];
vector<P>g[N];
int dep[N],fa[N],rf[N];
void dfs(int u,int p)
{
    fa[u]=p;dep[u]=dep[p]+1;
    for(auto &[v,w]:g[u]) if(v!=p) rf[v]=w,dfs(v,u);
}
void get(int x,int y,vector<int>&w)
{
    for(;dep[x]>dep[y];x=fa[x]) w.push_back(rf[x]^1);
    for(;dep[y]>dep[x];y=fa[y]) w.push_back(rf[y]);
    for(;x!=y;x=fa[x],y=fa[y]) w.push_back(rf[x]^1),w.push_back(rf[y]);
}
vector<int>p[N],id[N];int deg[N],vis[N],op[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(MP(v,2*i)),g[v].push_back(MP(u,2*i+1));
    dfs(1,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        get(x[i],y[i],p[i]);
        for(int v:p[i]) id[v/2].push_back(i),deg[v/2]++/*,printf("- %d ",v);puts("")*/;
    }
    long long ans=0;
    for(int i=1;i<n;i++) ans+=min(2,deg[i]);
    printf("%lld\n",ans);
    while(true)
    {
        int u=0,w=0;
        for(int i=1;i<n;i++) if(deg[i]==1 && op[i*2]!=op[i*2+1]){w=i;break;}
        if(!w) for(int i=1;i<n;i++) if(deg[i]>=2){w=i;break;}
        if(!w) break;
        for(int v:id[w]) if(!vis[v]){u=v;break;}
        vis[u]=true;
        for(int v:p[u]) if(v/2==w)
        {
            if(op[v]) swap(x[u],y[u]),for_each(p[u].begin(),p[u].end(),[&](int &x){x^=1;});
            for_each(p[u].begin(),p[u].end(),[&](int &x){deg[x/2]--,op[x]=true;});
        }
    }
    for(int i=1;i<=m;i++) printf("%d %d\n",x[i],y[i]);
    return 0;
}