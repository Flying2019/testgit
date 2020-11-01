#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
#define N 50
#define M 40000
#define mod 1000000007
#pragma GCC optimize(2,3)
#define vc vector
#define vci vector<int>
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
int fac[M],inv[M];
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
vci tm,c[M],v;
int cnt,w[M];
map<vci,int>mp;
vc<P >to[M];
void chai(int x,int p,int w)
{
    if(!x){c[++cnt]=tm;mp[tm]=cnt;::w[cnt]=w;return;}
    tm.push_back(p);
    for(int i=p;i<=x;i++,(*tm.rbegin())++) chai(x-i,i,w+i*(i-1)/2);
    tm.pop_back();
}
int A(int a,int b){return a<b?0:1ll*fac[a]*inv[a-b]%mod;}
int a[N],f[N][M];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n);chai(n,1,0);
    fac[0]=1;
    for(int i=1;i<=M-10;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[M-10]=ksm(fac[M-10]);
    for(int i=M-11;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int _=1;_<=cnt;_++)
    {
        auto u=c[_];int s=u.size();
        for(register int i=0;i<s;i++)
            for(register int j=i+1;j<s;j++)
            {
                v.clear();int sm=u[i]+u[j];
                for(int k=0;k<s;k++)
                if(k!=i && k!=j)
                {
                    if(sm && u[k]>=sm) v.push_back(sm),sm=0;
                    v.push_back(u[k]);
                }
                if(sm) v.push_back(sm);
                to[_].push_back(MP(mp[v],1ll*u[i]*u[j]%mod));
            }
    }
    f[0][1]=1;
    for(int i=0;i<n;i++)
        for(int j=1;j<=cnt;j++)
        {
            int v=1ll*f[i][j]*A(w[j]-a[i],a[i+1]-a[i]-1)%mod,*g=f[i+1];
            if(v) for(auto t:to[j]) g[t.fi]=(g[t.fi]+1ll*v*t.se)%mod;
        }
    printf("%d\n",1ll*f[n-1][cnt]*fac[n*(n-1)/2-a[n-1]]%mod);
    return 0;
}