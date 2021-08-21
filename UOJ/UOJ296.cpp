#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define S 600
#define mod1 1000000007
#define mod2 1000000009
#define il inline
using namespace std;
int ksm(int x,int y,int mod)
{
    int r=1;
    for(;y;y>>=1)
    {
        if(y&1) r=1ll*r*x%mod;
        x=1ll*x*x%mod;
    }
    return r;
}
struct P{
    int x,y;
    P(int X,int Y):x(X),y(Y){}
    P(int X=0):x((X+mod1)%mod1),y((X+mod2)%mod2){}
};
const int base=260000007;
const P iB=P(ksm(base,mod1-2,mod1),ksm(base,mod2-2,mod2));
const P iB1=P(ksm(base-1,mod1-2,mod1),ksm(base-1,mod2-2,mod2));//1/(b-1)
il int Add(int x,int y,int m){return x+y>=m?x+y-m:x+y;}
il int Dec(int x,int y,int m){return x-y<0?x-y+m:x-y;}
il P operator +(P a,P b){return P(Add(a.x,b.x,mod1),Add(a.y,b.y,mod2));}
il P operator -(P a,P b){return P(Dec(a.x,b.x,mod1),Dec(a.y,b.y,mod2));}
il P operator -(P a){return P(Dec(0,a.x,mod1),Dec(0,-a.y,mod2));}
il P operator *(P a,P b){return P(1ll*a.x*b.x%mod1,1ll*a.y*b.y%mod2);}
il bool operator ==(P a,P b){return a.x==b.x && a.y==b.y;}
P bs[N],iv[N];
int fl[N],fr[N],bl[N];
P hs[N],tga[N],tgb[N];
int n;
inline void push(int l,int r,P a,P b){for(int i=l;i<=r;i++) hs[i]=hs[i]+a*bs[i]+b;}
void add(int l,int r,P a,P b)
{
    if(l>r) return;
    int pl=bl[l],pr=bl[r];
    if(pl==pr) push(l,r,a,b);
    else
    {
        push(l,fr[pl],a,b);push(fl[pr],r,a,b);
        for(int i=pl+1;i<pr;i++) tga[i]=tga[i]+a,tgb[i]=tgb[i]+b;
    }
}
int tg[N],a[N];
inline void push(int l,int r,int v){for(int i=l;i<=r;i++) a[i]+=v;}
void add(int l,int r,int v)
{
    add(l,r,v*iv[l-1]*iB1,-v*iB1);
    add(r+1,n,v*iv[r]*(bs[r-l+1]-1)*iB1,0);
    int pl=bl[l],pr=bl[r];
    if(pl==pr) push(l,r,v);
    else
    {
        push(l,fr[pl],v);push(fl[pr],r,v);
        for(int i=pl+1;i<pr;i++) tg[i]+=v;
    }
}
P get(int u){return hs[u]+tga[bl[u]]*bs[u]+tgb[bl[u]];}
P get(int l,int r){return get(r)-get(l-1)*bs[r-l+1];}
int getv(int u){return a[u]+tg[bl[u]];}
int cmp(int x,int y,int p)
{
    p-=y;
    if(get(x,x+p)==get(y,y+p))return 0;
    if(getv(x)!=getv(y)) return getv(x)<getv(y)?-1:1;
    int l=0,r=p;
    while(l<=r)
    {
    	int mid=(l+r)>>1;
    	if(get(x,x+mid)==get(y,y+mid)) l=mid+1;
    	else r=mid-1,p=mid;
    }
    return getv(x+p)<getv(y+p)?-1:1;
}
vector<int>lyn[N<<2];
void update(int u,int r)
{
    auto &ul=lyn[u<<1],&ur=lyn[u<<1|1],&p=lyn[u];
    int mx=0;
    p.resize(ur.size()+1);
    for(int x:ul) if(!mx || cmp(mx,x,r)>0) mx=x;
    p[0]=mx;
    for(int i=0;i<ur.size();i++) p[i+1]=ur[i];
}
void build(int u,int l,int r)
{
    if(l==r){lyn[u].push_back(l);return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    update(u,r);
}
void update(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return;
    int mid=(l+r)>>1;
    if(L<=mid) update(u<<1,l,mid,L,R);
    if(R>mid) update(u<<1|1,mid+1,r,L,R);
    update(u,r);
}
int ans;
void answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R)
    {
        for(int v:lyn[u])
            if(!ans || cmp(ans,v,R)>=0) ans=v;
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) answer(u<<1,l,mid,L,R);
    if(R>mid) answer(u<<1|1,mid+1,r,L,R);
}
void init()
{
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]+=base/2,hs[i]=hs[i-1]*base+a[i];
    memset(fl,0x3f,sizeof(fl));
    for(int i=1;i<=n;i++) bl[i]=(i-1)/S+1,fl[bl[i]]=min(fl[bl[i]],i),fr[bl[i]]=max(fr[bl[i]],i);
    bs[0]=iv[0]=1;
    for(int i=1;i<=n+1;i++) bs[i]=bs[i-1]*base,iv[i]=iv[i-1]*iB;
}
int main()
{
    // freopen("UOJ296.in","r",stdin);
    // freopen("UOJ296.out","w",stdout);
    int q;
    scanf("%d%d",&n,&q);
    init();
    build(1,1,n);
    while(q --> 0)
    {
        int op,l,r,w;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)
        {
            scanf("%d",&w);
            add(l,r,w);
            update(1,1,n,l,r);
        }
        else
        {
            ans=0;
            answer(1,1,n,l,r);
            printf("%d\n",ans);
        }
    }
    return 0;
}