#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
#define N 600010
#define ll long long
using namespace std;
struct node{
    int x,y,w;
    bool operator <(const node a)const{return w<a.w;}
}r[N];
int fa[N];
int find(int x){return x==fa[x]?fa[x]:(fa[x]=find(fa[x]));}
vector<int>g[N],h[N];int w[N];
int mn[N],dep[N],mx[N],n;
void dfs(int u,int d)
{
    mn[u]=u; if(u<=n) return;
    for(int v:g[u]) dfs(v,d+1),mn[u]=min(mn[u],mn[v]),mx[u]=max(mx[u],mn[v]);
}
int main()
{
    int k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++) scanf("%d%d%d",&r[i].x,&r[i].y,&r[i].w);
    sort(r+1,r+n);
    for(int i=1;i<=n*2-1;i++) fa[i]=i;
    for(int i=1;i<n;i++)
    {
        int x=find(r[i].x),y=find(r[i].y);
        w[n+i]=r[i].w;
        g[n+i].push_back(x);g[n+i].push_back(y);
        fa[x]=fa[y]=n+i;
    }
    int s=n*2-1;
    dfs(s,0);ll sm=0;
    priority_queue<int,vector<int>,greater<int> >f;
    for(int i=1;i<=s;i++) h[mx[i]].push_back(i);
    for(int d=1;d<=n;d++,printf("%lld\n",sm))
        for(int u:h[d])
        {
            f.push(w[u]), sm+=w[u];
            if(f.size()>k) sm-=f.top(),f.pop();
        }
    return 0;
}