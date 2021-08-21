#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 50010
#define S(a) ((int)a.size())
#define inf 2000000000
#define pb push_back
#define For01(x) for(int x=0;x<=1;x++)
using namespace std;
typedef long long ll;
typedef vector<ll> vec;
vec R(vec a,int k){a.resize(k,-inf);return a;}
vec max(const vec &a,const vec &b)
{
    vec c=S(a)>S(b)?a:b;
    for(int i=0;i<min(S(a),S(b));i++) c[i]=max(a[i],b[i]);
    return c;
}
vec operator +(const vec &a,const vec &b)
{
    vec c;
    if(a.empty() || b.empty()) return c;
    c.reserve(S(a)+S(b));
    c.push_back(a[0]+b[0]);
    int p=1,q=1;ll w=a[0]+b[0];
    while(p<S(a) && q<S(b))
        if(a[p]-a[p-1]>b[q]-b[q-1]) c.push_back(w+=a[p]-a[p-1]),p++;
        else c.push_back(w+=b[q]-b[q-1]),q++;
    for(;p<S(a);p++) c.push_back(w+=a[p]-a[p-1]);
    for(;q<S(b);q++) c.push_back(w+=b[q]-b[q-1]);
    return c;
}
vec inc(vec a,int k=0){vec b(S(a)+k,-inf);for(ll v:a) b[k++]=v;return b;}
vec f[N<<2][2][2];
int a[N];
int ext(int l,int r,int x,int y){return (l || r)+(x || y)-(l || y)-(r && x);}
void build(int u,int l,int r)
{
    if(l==r){f[u][0][0].pb(0);For01(x) For01(y) f[u][x][y].pb(a[l]);return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    For01(l) For01(x) For01(y) For01(r)
    f[u][l][r]=max(f[u][l][r],inc(f[u<<1][l][x]+f[u<<1|1][y][r],ext(l,x,y,r)));
}
struct node{
    ll v;int u;
    node(ll V=-1e17,int U=0):v(V),u(U){}
    bool operator <(const node a)const{return v==a.v?u<a.u:v<a.v;}
    node operator +(const node a)const{return node(v+a.v,u+a.u);}
};
node g[2];
int pos[N<<2][2][2];
void solve(int u,int l,int r,int L,int R,int o)
{
    if(L<=l && r<=R)
    {
        node h[2]={node(),node()};
        For01(x) For01(y)
        {
            int &p=pos[u][x][y];
            for(;p && f[u][x][y][p]-f[u][x][y][p-1]<o;p--);
            ll v=f[u][x][y][p];
            h[y]=max(h[y],g[0]+node(v-1ll*o*(p+(x||y)),p+(x||y)));
            h[y]=max(h[y],g[1]+node(v-1ll*o*(p+(x||y)-x),p+(x||y)-x));
        }
        g[0]=h[0];g[1]=h[1];
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) solve(u<<1,l,mid,L,R,o);
    if(R>mid) solve(u<<1|1,mid+1,r,L,R,o);
}
void clear(int u,int l,int r)
{
    For01(x) For01(y) pos[u][x][y]=S(f[u][x][y])-1;
    if(l==r) return;
    int mid=(l+r)>>1;clear(u<<1,l,mid);clear(u<<1|1,mid+1,r);
}
int l[N],r[N],w[N];ll res[N];
struct ques{
    int l,r,u;
}q[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&l[i],&r[i],&w[i]);
    for(int i=1;i<=m;i++) q[i]=(ques){-inf,inf,i};
    build(1,1,n);
    for(int _=50;_;_--)
    {
        clear(1,1,n);
        sort(q+1,q+m+1,[&](ques a,ques b){return (a.l+a.r)/2<(b.l+b.r)/2;});
        for(int i=1;i<=m;i++)
        if(q[i].l<=q[i].r)
        {
            int mid=(q[i].l+q[i].r)>>1;
            g[0]=node(0,0);g[1]=node();
            solve(1,1,n,l[q[i].u],r[q[i].u],mid);
            node t=max(g[0],g[1]);
            if(t.u>=w[q[i].u]) q[i].l=mid+1,res[q[i].u]=t.v+1ll*mid*w[q[i].u];
            else q[i].r=mid-1;
            if(t.u==w[q[i].u]) q[i].r=mid;
        }
    }
    for(int i=1;i<=m;i++) printf("%lld\n",res[i]);
    return 0;
}