#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define fi first
#define se second
using namespace std;
typedef pair<int,int> P;
typedef vector<int> vec;
vec g[N];
bool cut[N];
int siz[N],mx[N],rt,all;
void dfs0(int u,int p)
{
    siz[u]=1;
    for(int v:g[u]) if(v!=p && !cut[v]) dfs0(v,u),siz[u]+=siz[v];
}
void dfs1(int u,int p)
{
    mx[u]=1;
    for(int v:g[u])
    if(v!=p && !cut[v]) dfs1(v,u),mx[u]=max(mx[u],siz[v]);
    mx[u]=max(mx[u],all-siz[u]);
    if(!rt || mx[u]<mx[rt]) rt=u;
}
int qry(const vec &w,int x)
{
    printf("? %d %d",(int)w.size(),x);
    for(int v:w) printf(" %d",v);
    puts("");fflush(stdout);
    scanf("%d",&x);
    return x;
}
int ch[N],sz[N],tt;
int search(int u)
{
    int l=1,r=tt,p=l;
    while(l<r)
    {
        int mid=lower_bound(sz+l,sz+r+1,(sz[r]+sz[l-1])/2)-sz;
        if(!qry({ch[mid]},u)) return ch[mid];
        if(l==mid){l++;continue;}if(r==mid){r--;continue;}
        if(qry(vec(ch+l,ch+mid),u)) l=mid+1;
        else r=mid-1;
    }
    return ch[r];
}
void solve(int u)
{
    dfs0(u,0);
    all=siz[u];rt=0;
    dfs1(u,0);u=rt;
    cut[u]=true;
    if(all==1){printf("! %d\n",u);return;}
    tt=0;
    for(int v:g[u])
    if(!cut[v]) dfs0(v,u),ch[++tt]=v,sz[tt]=sz[tt-1]+siz[v];
    if(qry(vec(ch+1,ch+tt+1),u)){printf("! %d\n",u);return;}
    solve(search(u));
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);g[v].push_back(u);
    }
    solve(1);
    return 0;
}