#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#define N 300010
#define M 1000010
#define P pair<int,int>
#define MP make_pair
using namespace std;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int x[N],y[N],z[N];
typedef vector<int> vec;
vec px,py,pz,nx[M],ny[M],nz[M];
map<P,int>sx,sy,sz;
int f[M];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
void merge(int x,int y){f[find(x)]=find(y);}
void merge(int u,vec &x)
{
    if(x.empty()) return;
    for(int v:x) merge(u,v);
    x.clear();x.push_back(find(u));
}
void prework(map<P,int>&s,vector<int>&p,int x[],int y[])
{
    for(int u:p)
        for(int i=0;i<4;i++)
        if(s.count(MP(x[u]+dx[i],y[u]+dy[i])))
            merge(u,s[MP(x[u]+dx[i],y[u]+dy[i])]);
}
int id(int x,int y,int z)
{
    if(sx.count(MP(y,z))) return sx[MP(y,z)];
    if(sy.count(MP(x,z))) return sy[MP(x,z)];
    if(sz.count(MP(x,y))) return sz[MP(x,y)];
    return 0;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&x[i],&y[i],&z[i]);
            if(x[i]==-1) px.push_back(i),sx[MP(y[i],z[i])]=i;
            if(y[i]==-1) py.push_back(i),sy[MP(x[i],z[i])]=i,nz[z[i]].push_back(i);
            if(z[i]==-1) pz.push_back(i),sz[MP(x[i],y[i])]=i,nx[x[i]].push_back(i),ny[y[i]].push_back(i);
        }
        for(int i=1;i<=n;i++) f[i]=i;
        prework(sx,px,y,z);prework(sy,py,x,z);prework(sz,pz,x,y);
        for(int u:px)
            for(int i=-1;i<=1;i++) merge(u,nz[z[u]+i]);
        for(int u:px)
            for(int i=-1;i<=1;i++) merge(u,ny[y[u]+i]);
        for(int u:py)
            for(int i=-1;i<=1;i++) merge(u,nx[x[u]+i]);
        int q;
        scanf("%d",&q);
        while(q --> 0)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            int u=id(x,y,z);
            scanf("%d%d%d",&x,&y,&z);
            int v=id(x,y,z);
            if(!u || !v) puts("NO");
            puts(find(u)==find(v)?"YES":"NO");
        }
        sx.clear();sy.clear();sz.clear();
        px.clear();py.clear();pz.clear();
        for(int i=0;i<=M-10;i++) nx[i].clear(),ny[i].clear(),nz[i].clear(),f[i]=0;
    }
    return 0;
}