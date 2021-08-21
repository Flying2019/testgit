#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
#define N 16
#define db long double
#define ll long long
#define inf 1e16
using namespace std;
ll w[N];
struct node{
    ll x,y;
}p[N],tmp[N];
db dis(node a,node b){return sqrt((db)(a.x-b.x)*(a.x-b.x)+(db)(a.y-b.y)*(a.y-b.y));}
int n;
int fa[N];
int find(int x){return x==fa[x]?fa[x]:(fa[x]=find(fa[x]));}
struct road{
    int x,y;db w;
    bool operator <(road a){return w<a.w;}
}rd[N*N];
db f[1<<N],g[1<<N];
db calc(int s)
{
    int tt=0;db res=0;
    for(int i=0;i<n;i++)
    if((s>>i)&1) tmp[++tt]=p[i],res+=w[i];
    for(int i=1;i<=tt;i++) fa[i]=i;
    int rt=0;
    for(int i=1;i<=tt;i++)
        for(int j=i+1;j<=tt;j++) rd[++rt]=(road){i,j,dis(tmp[i],tmp[j])};
    sort(rd+1,rd+rt+1);
    for(int i=1;i<=rt;i++)
    if(find(rd[i].x)!=find(rd[i].y)) res-=rd[i].w,fa[find(rd[i].x)]=find(rd[i].y);
    return res/tt;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld%lld%lld",&p[i].x,&p[i].y,&w[i]);
    int m=1<<n;
    for(int i=1;i<m;i++) g[i]=calc(i);
    f[0]=inf;
    for(int i=1;i<m;i++)
    {
        f[i]=g[i];
        for(int s=i&(i-1);s;s=(s-1)&i) f[i]=max(f[i],min(f[i^s],g[s]));
    }
    cout<<fixed<<setprecision(18)<<f[m-1];
    return 0;
}