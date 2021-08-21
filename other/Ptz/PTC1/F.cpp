#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 200010
using namespace std;
struct node{
    int op,x,y,w;
    bool operator <(const node a)const{return w==a.w?op>a.op:w>a.w;}
}r[N];
int f[N],F[N],G[N];
vector<int>g[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int Find(int x){return x==F[x]?F[x]:(F[x]=Find(F[x]));}
bool tag[N];int cut[N];
void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    if(g[x].size()<g[y].size()) swap(x,y);
    for(int i=0;i<g[y].size();i++)
    {
        if(i<cut[y]) tag[g[y][i]]=true;
        g[x].push_back(g[y][i]);
    }
    f[y]=x;
}
void Merge(int x,int y)
{
    x=Find(x);y=Find(y);
    if(x==y) return;
    F[y]=x;G[x]+=G[y];
}
void Tag(int x)
{
    int x1=find(x),x2=Find(x);
    if(g[x1].size()!=G[x2]) cut[x1]=g[x1].size();
}
int nxt[N<<1],to[N<<1],head[N],cnt;
void add(int u,int v)
{
    nxt[++cnt]=head[u];
    to[cnt]=v;head[u]=cnt;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d%d",&r[i].op,&r[i].x,&r[i].y,&r[i].w);
    sort(r+1,r+m+1);
    for(int i=1;i<=n;i++) f[i]=F[i]=i,g[i].push_back(i),G[i]=1;
    for(int i=1,j=1;i<=m;i=j)
    {
        for(;j<=m && r[j].w==r[i].w;j++)
        {
            Merge(r[j].x,r[j].y);
            if(r[j].op==1) merge(r[j].x,r[j].y);
        }
        for(int k=i;k<j;k++) Tag(r[k].x),Tag(r[k].y);
    }
    for(int i=1;i<=n;i++)
    if(f[i]==i) for(int j=0;j<cut[i];j++) tag[g[i][j]]=true;
    int s=0;
    for(int i=1;i<=n;i++) s+=!tag[i];
    printf("%d\n",s);
    for(int i=1;i<=n;i++)
        if(!tag[i]) printf("%d ",i);
    return 0;
}