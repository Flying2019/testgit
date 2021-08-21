#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<set>
#define N 200010
#define fi first
#define se second
#define MP make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const ll MX=20000000000,inf=1000000000000000;
int a[N];
struct line{
    ll k,b;
    line(ll K=0,ll B=0):k(K),b(B){}
    ll operator ()(ll x){return k*x+b;}
};
namespace LiCT{
    int rt1[N<<2],rt2[N<<2];
    const int M=N*20;
    line v[M];int tt;
    int ls[M],rs[M];
    void insg(int &u,ll l,ll r,line t)
    {
        if(!u){u=++tt;v[u]=t;return;}
        ll mid=(l+r)>>1;
        if(v[u](mid)<t(mid)) swap(v[u],t);
        if(v[u](l)<t(l)) insg(ls[u],l,mid,t);
        if(v[u](r)<t(r)) insg(rs[u],mid+1,r,t);
    }
    ll qryg(int u,ll l,ll r,ll p)
    {
        if(!u) return -inf;
        ll mid=(l+r)>>1;
        if(p<=mid) return max(v[u](p),qryg(ls[u],l,mid,p));
        else return max(v[u](p),qryg(rs[u],mid+1,r,p));
    }
    void ins1(int u,int l,int r,int p,line v)
    {
        if(p<l) return;
        insg(rt1[u],0,N,v);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) ins1(u<<1,l,mid,p,v);
        else ins1(u<<1|1,mid+1,r,p,v);
    }
    void ins2(int u,int l,int r,int L,int R,line v)
    {
        if(R<L || R<l || r<L) return;
        if(L<=l && r<=R){insg(rt2[u],0,MX,v);return;}
        int mid=(l+r)>>1;
        ins2(u<<1,l,mid,L,R,v),ins2(u<<1|1,mid+1,r,L,R,v);
    }
    ll qry1(int u,int l,int r,int L,int R,ll x)
    {
        if(R<L || R<l || r<L) return -inf;
        if(L<=l && r<=R) return qryg(rt1[u],0,N,x);
        int mid=(l+r)>>1;
        return max(qry1(u<<1,l,mid,L,R,x),qry1(u<<1|1,mid+1,r,L,R,x));
    }
    ll qry2(int u,int l,int r,int p,ll x)
    {
        if(p<l) return -inf;
        if(l==r) return qryg(rt2[u],0,MX,x);
        int mid=(l+r)>>1;
        if(p<=mid) return max(qryg(rt2[u],0,MX,x),qry2(u<<1,l,mid,p,x));
        else return max(qryg(rt2[u],0,MX,x),qry2(u<<1|1,mid+1,r,p,x));
    }
}
using LiCT::qry1;using LiCT::qry2;using LiCT::ins1;using LiCT::ins2;
namespace SegT{
    int val[N<<2];
    void setg(int u,int v){val[u]=max(val[u],v);return;}
    void ins(int u,int l,int r,int L,int R,int v)
    {
        if(L<=l && r<=R){setg(u,v);return;}
        int mid=(l+r)>>1;
        if(L<=mid) ins(u<<1,l,mid,L,R,v);
        if(R>mid) ins(u<<1|1,mid+1,r,L,R,v);
    }
    int qry(int u,int l,int r,int p)
    {
        if(p<l) return 0;
        if(l==r) return val[u];
        int mid=(l+r)>>1;
        if(p<=mid) return max(val[u],qry(u<<1,l,mid,p));
        else return max(val[u],qry(u<<1|1,mid+1,r,p));
    }
}
using SegT::ins;using SegT::qry;
ll s[N];
vector<int>b[N];
set<P>st;
struct segs{
    int l,r,x;
    segs(int L=0,int R=0,int V=0):l(L),r(R),x(V){}
};
vector<segs>d[N];
int las[N];ll f[N];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[a[i]].push_back(i),s[i]=s[i-1]+a[i];
    for(int i=0;i<=n+1;i++) b[i].push_back(n+1),st.insert(MP(i,i));
    for(int i=0;i<=n;i++)
    {
        int x=0;
        for(int y:b[i])
        {
            if(y-x>=2)
            {
                auto p=st.lower_bound(MP(x+1,0));
                // printf("find %d -> %d %d\n",x,p->fi,p->se);
                if(p->se<y)
                {
                    int py=p->se,px=p->fi;
                    for(;p->se<y;st.erase(p++))
                        d[p->se].push_back(segs(x+1,p->fi,i)),px=p->fi;
                    st.insert(MP(x,py)),st.insert(MP(px,y));
                    // printf("add %d %d\n",x,py);printf("add %d %d\n",px,y);
                    // for(auto u:st) printf("%d,%d ",u.fi,u.se);puts("");
                }
            }
            x=y;
        }
    }
    ins1(1,1,n,1,line(0,0));
    for(int i=1;i<=n;i++)
    {
        for(segs v:d[i])
        {
            las[v.x]=v.r;
            ins(1,1,n,v.l,v.r,v.x);
            ins2(1,1,n,i,v.l+k-1,line(v.x,qry1(1,1,n,v.l,v.r,v.x)));
        }
        f[i]=qry2(1,1,n,i,s[i]);
        int x=qry(1,1,n,i-k+1);
        f[i]=max(f[i],qry1(1,1,n,i-k+1,las[x],x)+1ll*x*s[i]);
        ins1(1,1,n,i+1,line(-s[i],f[i]));
    }
    printf("%lld\n",f[n]);
    return 0;
}