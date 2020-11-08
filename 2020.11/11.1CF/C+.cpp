#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 1000010
#define MP make_pair
#define P pair<int,int>
#define vi vector<int>
#define ll long long
map<P,vi >mp; map<P,bool>vis;
vi road,rd[N],d[N],r[N];
int cr[N],ban[N],col[N],id[N],x[N],y[N],tot;
void add(int u,int v){road.push_back(u),road.push_back(v),rd[u].push_back(v),rd[v].push_back(u);}
bool dfs(int u)
{
    id[u]=tot-col[u];
    for(auto v:r[u])
    if(cr[u]==cr[v])
    {
        if(col[v]!=-1){if(col[u]==col[v])return false;}
        else{col[v]=col[u]^1;if(!dfs(v))return false;}
    }
    return true;
}
bool dfs2(int u)
{
    for(auto v:rd[u])
    if(col[v]!=-1){if(col[u]==col[v]) return false;}
    else{col[v]=col[u]^1;if(!dfs2(v)) return false;}
    return true;
}
bool check()
{
    sort(road.begin(),road.end());
    road.erase(unique(road.begin(),road.end()),road.end());
    int pre=-1;
    for(auto u:road){if(pre==((u-1)^1)+1) rd[u].push_back(pre),rd[pre].push_back(u);pre=u;}
    for(auto u:road) col[u]=-1;
    for(auto u:road) if(col[u]==-1){col[u]=0;if(dfs2(u)) return false;}
    return true;
}
int main()
{
    ll ans=0;int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&cr[i]),d[cr[i]].push_back(i);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        r[u].push_back(v),r[v].push_back(u);
        if(cr[u]>cr[v]) swap(u,v);x[i]=u,y[i]=v;
        mp[MP(cr[u],cr[v])].push_back(i);
    }
    memset(col,-1,sizeof(col));
    for(int i=1;i<=k;i++)
    {
        ban[i]=false;
        for(int u:d[i])
        if(col[u]==-1)
        {
            col[u]=0;tot+=2;
            if(!dfs(u)){ban[u]=true;break;}
        }
    }
    int cnt=0;
    for(int i=1;i<=k;i++) cnt+=!ban[i];
    ans=1ll*cnt*(cnt-1)/2;
    for(int i=1;i<=m;i++)
    if(cr[x[i]]!=cr[y[i]])
    {
        auto u=MP(cr[x[i]],cr[y[i]]);
        if(vis[u]) continue;
        vis[u]=1;
        for(auto k:mp[u]) add(id[x[k]],id[y[k]]);
        if(check()) --ans;
        for(auto u:road) rd[u].clear();road.clear();
    }
    printf("%lld\n",ans);
    return 0;
}
