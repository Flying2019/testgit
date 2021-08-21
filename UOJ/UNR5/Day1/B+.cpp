#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#define ll long long
using namespace std;
const int N=400010,mod=998244353,G=3,Gi=(mod+1)/G;
inline int sub(int x,int y){return x<y?x+mod-y:x-y;}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
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
namespace NTT{
	int rev[N<<2];
	int get_rev(int n)
	{
		int lim=1,l=0;
		for(;lim<=n;lim<<=1) l++;
		for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return lim;
	}
	void ntt(int f[],int lim,int op)
	{
		for(int i=0;i<lim;i++)
		if(i<rev[i]) swap(f[rev[i]],f[i]);
		for(int mid=1;mid<lim;mid<<=1)
		{
			int r=ksm(op==1?G:Gi,(mod-1)/(mid*2));
			for(int i=0;i<lim;i+=mid<<1)
				for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
				{
					int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
					f[i+j]=add(x,y);f[i+j+mid]=sub(x,y);
				}
		}
		if(op==-1)
		{
			int r=ksm(lim);
			for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
		}
	}
}
using NTT::get_rev;
using NTT::ntt;
typedef vector<int> poly;
#define pb push_back
#define For_poly(i,p) for(int i=0;i<S(p);i++)
int S(poly &a){return a.size();}
void init(poly &a,int n){a.resize(n);}
void init(vector<poly*>a,int n){for(auto p:a) init(*p,n);}
poly operator >>(poly a,int p){return poly(a.begin()+p,a.end());}
void print(poly &a){For_poly(i,a) printf("%d ",a[i]);puts("");}
poly operator +(poly a,poly b)
{
	init(a,max(S(a),S(b)));
	For_poly(i,b) a[i]=add(a[i],b[i]);
	return a;
}
poly operator -(poly a,poly b)
{
	init(a,max(S(a),S(b)));
	For_poly(i,b) a[i]=sub(a[i],b[i]);
	return a;
}
poly operator *(poly a,int x)
{
	For_poly(i,a) a[i]=1ll*a[i]*x%mod;
	return a;
}
poly operator *(poly a,poly b)
{
	if(!S(a) || !S(b)) return poly();
	int m=S(a)+S(b)-1,lim=get_rev(m);
	poly c;init({&a,&b,&c},lim);
	ntt(&a[0],lim,1);ntt(&b[0],lim,1);
	for(int i=0;i<lim;i++) c[i]=1ll*a[i]*b[i]%mod;
	ntt(&c[0],lim,-1);
	init(c,m);
	return c;
}
int n,aiv=1;
vector<int>g[N];
namespace Root{
    int siz[N],mx,rt;
    void dfs(int u,int p,int all)
    {
        siz[u]=1;
        int mr=0;
        for(int v:g[u]) if(v!=p) dfs(v,u,all),siz[u]+=siz[v],mr=max(mr,siz[v]);
        mr=max(mr,all-siz[u]);
        if(!rt || mx>mr) rt=u,mx=mr;
    }
    int find(int all){dfs(1,0,all);return rt;}
}
namespace Hs{
    typedef pair<int,int> P;
    #define MP make_pair
    #define fi first
    #define se second
    P operator +(const P a,const P b){return MP((a.fi+b.fi)%mod,(a.se+b.se)%mod);}
    P operator +(const P a,const int b){return MP((a.fi+b)%mod,(a.se+b)%mod);}
    P operator -(const P a,const P b){return MP((a.fi-b.fi+mod)%mod,(a.se-b.se+mod)%mod);}
    P operator *(const P a,const P b){return MP((1ll*a.fi*b.fi)%mod,(1ll*a.se*b.se)%mod);}
    P drand[N],h[N];
    int siz[N];
    map<P,P>f[N];
    void dfs(int u,int p)
    {
        h[u]=MP(1,1);siz[u]=1;
        for(int v:g[u]) if(v!=p)
        {
            dfs(v,u);siz[u]+=siz[v];
            if(!f[u].count(h[v])) f[u][h[v]]=MP(v,1);
            else f[u][h[v]].se++,aiv=1ll*aiv*ksm(f[u][h[v]].se)%mod;
            h[u]=h[u]*(h[v]+1);
        }
        h[u]=h[u]+drand[siz[u]];
    }
    int rand0(){return ((1ll*rand()<<18)^rand())%mod;}
    void init(){srand(114514);for(int i=1;i<=n*2;i++) drand[i]=MP(rand0(),rand0());}
}
int fac[N],inv[N];
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
poly solve_pow(poly a[],int l,int r,int n)
{
    if(l==r){return {(int)(1ll*fac[n]*inv[l]%mod)};}
    int w=0;
    while((1<<(w+1))<=r-l) w++;
    return solve_pow(a,l,l+(1<<w)-1,n)+solve_pow(a,l+(1<<w),r,n)*a[w];
}
poly solve_mul(poly a[],int l,int r)
{
    if(l==r) return {a[r]};
    int mid=(l+r)>>1;
    return solve_mul(a,l,mid)*solve_mul(a,mid+1,r);
}
poly f[N],c[N];
poly tn[N];int tt;
int siz[N];
void set_f(int s){init(tn[++tt],s+1);For_poly(i,tn[tt]) tn[tt][i]=C(s,i);}
void solve(int u,int w=1,int p=0,bool root=true)
{
    siz[u]=u<=n;
    int l=tt;
    for(auto t:Hs::f[u])
        solve(t.se.fi,t.se.se,u,false),siz[u]+=siz[t.se.fi];
    if(w>1 || root)
    {
        set_f(siz[u]);siz[u]=0;
        f[u]=solve_mul(tn,l+1,tt);tt=l;
        c[0]=f[u];
        int iv=ksm(f[u][0]),v=ksm(f[u][0],w);
        For_poly(i,c[0]) c[0][i]=1ll*c[0][i]*iv%mod;
        c[0][0]=0;
        for(int i=1;(1<<i)<=w;i++) c[i]=c[i-1]*c[i-1];
        tn[++tt]=solve_pow(c,0,w,w);
        For_poly(i,tn[tt]) tn[tt][i]=1ll*tn[tt][i]*v%mod;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[n+i].pb(v),g[n+i].pb(u);
        g[v].pb(n+i),g[u].pb(n+i);
    }
    init();
    Hs::init();
    int rt=Root::find(n*2-1);
    Hs::dfs(rt,0);
    solve(rt);
    for(int i=1;i<S(f[rt]);i++) printf("%d ",1ll*f[rt][i]*fac[i]%mod*aiv%mod);
    return 0;
}