#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
int a[N],b[N];
vector<int>g[N];
int mn[N][2],mx[N][2];
int col[N],id[N];
void dfs(int u,int c,int mx[],int mn[])
{
    col[u]=c;
    mn[c]=min(mn[c],a[u]);mx[c]=max(mx[c],a[u]);
    mn[!c]=min(mn[!c],b[u]);mx[!c]=max(mx[!c],b[u]);
    for(int v:g[u])
    if(col[v]==-1) dfs(v,!c,mx,mn);
    else if(col[v]==c) mn[0]=mn[1]=0,mx[0]=mx[1]=inf;
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        int n,m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) col[i]=-1;
        for(int i=1;i<=m;i++)
        {
            int u,v;scanf("%d%d",&u,&v);
            g[u].push_back(v);g[v].push_back(u);
        }
        for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
        bool can=true;
        int s=0;
        for(int i=1;i<=n;i++)
        if(col[i]==-1)
        {
            ++s;
            mn[s][0]=mn[s][1]=inf;mx[s][0]=mx[s][1]=0;
            dfs(i,0,mx[s],mn[s]);
            if(mn[s][0]<mn[s][1]) swap(mx[s][0],mx[s][1]),swap(mn[s][0],mn[s][1]);
            if(mn[s][0]==0){can=false;break;}
        }
        if(!can) printf("Case %d: IMPOSSIBLE\n",_);
        else
        {
            int tt=0,res=inf,rmx=0,ans=inf;
            for(int i=1;i<=s;i++) res=min(res,mn[i][0]);
            for(int i=1;i<=s;i++)
            if(mx[i][0]>mx[i][1]) id[++tt]=i;
            else rmx=max(rmx,mx[i][0]);
            sort(id+1,id+tt+1,[&](int x,int y){return mx[x][0]>mx[y][0];});
            for(int i=1;i<=tt;i++)
            {
                int u=id[i];
                if(mx[u][0]<rmx) break;
                ans=min(ans,mx[u][0]-res);
                res=min(res,mn[u][1]);
                rmx=max(rmx,mx[u][1]);
            }
            ans=min(ans,rmx-res);
            printf("Case %d: %d\n",_,ans);
        }
        for(int i=1;i<=n;i++) g[i].clear(),col[i]=-1,a[i]=b[i]=id[i]=0;
    }
    return 0;
}