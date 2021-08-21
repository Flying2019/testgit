#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=500010,mod=998244353,inf=1000000000;
int a[N],pos[N],n,c;
int fac[N],inv[N];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
namespace SegTree{
    int val[N<<2];
    void build(int u,int l,int r)
    {
        if(l==r){val[u]=a[l];return;}
        int mid=(l+r)>>1;
        build(u<<1,l,mid);build(u<<1|1,mid+1,r);
        val[u]=min(val[u<<1],val[u<<1|1]);
    }
    void insert(int u,int l,int r,int p)
    {
        if(l==r){val[u]=inf;return;}
        int mid=(l+r)>>1;
        if(p<=mid) insert(u<<1,l,mid,p);
        else insert(u<<1|1,mid+1,r,p);
        val[u]=min(val[u<<1],val[u<<1|1]);
    }
    int answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return val[u];
        int mid=(l+r)>>1;
        if(R<=mid) return answer(u<<1,l,mid,L,R);
        if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
        return min(answer(u<<1,l,mid,L,R),answer(u<<1|1,mid+1,r,L,R));
    }
    int qry(int l,int r){return pos[answer(1,1,n,l,r)];}
    void del(int p){insert(1,1,n,p);}
}
using SegTree::qry;using SegTree::del;
int solve(int l,int r,int L,int R)
{
    if(r-l+1<c) return 1;
    if(c*(L+R)>r-l+1)
    {
        int w=max(L-1,0)+max(R-1,0);
        return fac[(r-l+1)-w];
    }
    int p=qry(l,r);del(p);
    if(p<l+c*L) return 1ll*solve(l,r,L+1,R)*(c*L-(L-1))%mod;
    if(p>r-c*R) return 1ll*solve(l,r,L,R+1)*(c*R-(R-1))%mod;
    return 1ll*solve(l,p-1,L,1)*solve(p+1,r,1,R)%mod;
}
void work()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),pos[a[i]]=i;
    SegTree::build(1,1,n);
    printf("%d\n",solve(1,n,0,0));
}
void pre_init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int main()
{
    pre_init();
    int t;
    scanf("%d",&t);
    while(t --> 0) work();
    return 0;
}