#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3010
#define pb push_back
#define S(x) ((int)x.size())
#define MP make_pair
#define fi first
#define se second
#define mod 998244353
using namespace std;
int n;
vector<int>g[N];
namespace Root{
    int siz[N],mx,rt;
    void dfs(int u,int p)
    {
        siz[u]=1;
        int mr=0;
        for(int v:g[u]) if(v!=p) dfs(v,u),siz[u]+=siz[v],mr=max(mr,siz[v]);
        mr=max(mr,n-siz[u]);
        if(!rt || mx>mr) rt=u,mx=mr;
    }
    int find(){dfs(1,0);return rt;}
}
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
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int f[N][N],sf[N],ss[N],sg[N];
string dfs(int u,int p)
{
    vector<pair<string,int> > son;
    for(int v:g[u]) if(v!=p) son.push_back(MP(dfs(v,u),v));
    sort(son.begin(),son.end());
    for(int i=0;i<=n;i++) sf[i]=0;
    f[u][0]=1;
    for(int l=0,r=0;l<S(son);l=r)
    {
        for(int p=0;p<=n;p++) sf[p]=0;
        sf[0]=1;
        for(r=l+1;r<S(son) && son[l].fi==son[r].fi;r++);
        int v=son[l].se;
        for(int p=0;p<=n;p++) ss[p]=f[u][p];
        for(int i=l;i<r;i++)
        {
            for(int p=0;p<=n;p++) sg[p]=sf[p],sf[p]=0;
            for(int p=0;p<=n;p++)
                for(int j=1;j<=p;j++)
                    sf[p]=(sf[p]+1ll*sg[p-j]*f[v][j]%mod*C(p,j))%mod;
            for(int p=0;p<=n;p++)
                for(int j=0;j<=p;j++)
                    f[u][p]=(f[u][p]+1ll*sf[j]*ss[p-j]%mod*inv[i-l+1]%mod*C(p,j))%mod;
        }
    }
    for(int p=n-1;p>=0;p--) f[u][p+1]=(f[u][p+1]+1ll*f[u][p]*(p+1)%mod)%mod;
    string a;
    for(auto v:son) a+="0"+v.fi+"1";
    return a;
}
int main()
{
    init();
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].pb(v),g[v].pb(u);
    int u=Root::find();Root::dfs(u,0);
    for(int v:g[u])
    if(Root::siz[v]*2==n)
    {
        auto a=dfs(u,v),b=dfs(v,u);
        if(a==b)
        {
            for(int p=0;p<=n;p++) sf[p]=0;
            f[0][0]=1;
            sf[0]=1;
            u=0;
            for(int p=0;p<=n;p++) ss[p]=f[u][p];
            for(int i=1;i<=2;i++)
            {
                for(int p=0;p<=n;p++) sg[p]=sf[p],sf[p]=0;
                for(int p=0;p<=n;p++)
                    for(int j=1;j<=p;j++)
                        sf[p]=(sf[p]+1ll*sg[p-j]*f[v][j]%mod*C(p,j))%mod;
                for(int p=0;p<=n;p++)
                    for(int j=0;j<=p;j++)
                        f[u][p]=(f[u][p]+1ll*sf[j]*ss[p-j]%mod*inv[i]%mod*C(p,j))%mod;
            }
        }
        break;
    }
    if(u) dfs(u,0);
    for(int i=1;i<=n;i++) printf("%d ",f[u][i]);
    return 0;
}