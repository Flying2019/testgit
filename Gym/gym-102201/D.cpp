#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 250010
#define ll long long
#define fi first
#define se second
#define inf 10000000000000000ll
using namespace std;
int n,sx,sy,tx,ty;
int ax[N],ay[N],bx[N],by[N];
void swapx()
{
    int mx=max(sx,tx);for(int i=1;i<=n;i++) mx=max(mx,max(ax[i],bx[i]));
    sx=mx-sx;tx=mx-tx;for(int i=1;i<=n;i++) ax[i]=mx-ax[i],bx[i]=mx-bx[i],swap(ax[i],bx[i]);
}
void swapy()
{
    int mx=max(sy,ty);for(int i=1;i<=n;i++) mx=max(mx,max(ay[i],by[i]));
    sy=mx-sy;ty=mx-ty;for(int i=1;i<=n;i++) ay[i]=mx-ay[i],by[i]=mx-by[i],swap(ay[i],by[i]);
}
void swapxy(){swap(sx,sy);swap(tx,ty);for(int i=1;i<=n;i++) swap(ax[i],ay[i]),swap(bx[i],by[i]);}
map<int,ll>s;
ll ans=0;
struct node{
    int x,y1,y2;
    bool operator <(const node a)const{return x<a.x;}
}p[N];
ll answer()
{
    int tt=0;
    s.clear();
    for(int i=1;i<=n;i++)
    if(ax[i]>=sx && ax[i]<=tx) p[++tt]=(node){ax[i],ay[i],by[i]};
    sort(p+1,p+tt+1);
    s[sy]=0;
    for(int i=1;i<=tt;i++)
    {
        auto pl=s.upper_bound(p[i].y1),pr=s.upper_bound(p[i].y2);
        if(pl==pr) continue;
        ll sl=inf,sr=inf;
        for(auto u=pl;u!=pr;u++) sl=min(sl,u->se+(u->fi-p[i].y1)),sr=min(sr,u->se+(p[i].y2-u->fi));
        s.erase(pl,pr);
        s[p[i].y1]=sl,s[p[i].y2]=sr;
    }
    if(ty<s.begin()->fi || ty>s.rbegin()->fi) return inf;
    ll res=inf;
    for(auto p:s)
    res=min(res,p.se+abs(ty-p.fi));
    return res+(tx-sx);
}
int main()
{
    scanf("%d%d%d%d%d",&n,&sx,&sy,&tx,&ty);
    for(int i=1;i<=n;i++) scanf("%d%d%d%d",&ax[i],&ay[i],&bx[i],&by[i]);
    if(sx>tx) swapx();if(sy>ty) swapy();
    ll a1=answer();
    swapxy();
    ll a2=answer();
    if(a1==inf && a2==inf){printf("%d\n",tx-sx+ty-sy);return 0;}
    printf("%lld\n",min(a1,a2));
    return 0;
}