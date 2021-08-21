#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define mod 1000000007
#define vec vector<int>
using namespace std;
const int N=60,M=5000010;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
namespace matrix{
    int a[N][N];
    void clear(int n){for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=0;}
    int gauss(int n)
    {
        int fl=1;
        for(int i=1;i<=n;i++)
        {
            int u=i;
            for(int j=i;j<=n;j++) if(a[i][j]){u=i;break;}
            if(u!=i){fl=mod-fl;swap(a[i],a[u]);}
            int iv=ksm(a[i][i]);
            for(int j=i+1;j<=n;j++)
            {
                int r=1ll*a[j][i]*iv%mod;
                for(int k=i;k<=n;k++) a[j][k]=(a[j][k]-1ll*a[i][k]*r%mod+mod)%mod;
            }
        }
        for(int i=1;i<=n;i++) fl=1ll*fl*a[i][i]%mod;
        return fl;
    }
}
int fac[M],inv[M];
void init(int n=M-10)
{
    for(int i=fac[0]=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int n,m;
vector<int>a,p[N];
int qry(vec &u,vec &v)
{
    for(int i=1;i<=n;i++) if(u[i]>v[i]) return 0;
    int t=0;
    for(int i=1;i<=n;i++) t+=v[i]-u[i];
    matrix::clear(n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) matrix::a[i][j]=u[i]<=v[j]?inv[v[j]-u[i]]:0;
    return 1ll*fac[t]*matrix::gauss(n)%mod;
}
int f[N];
int main()
{
    init();
    scanf("%d%d",&n,&m);
    a.resize(n+1);
    for(int i=0;i<=m;i++) p[i].resize(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]+=i;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) scanf("%d",&p[i][j]),p[i][j]+=j;
    sort(p+1,p+m+1);
    for(int i=1;i<=n;i++) p[0][i]=i;
    for(int i=m;i>=0;i--)
    {
        f[i]=qry(p[i],a);
        for(int j=i+1;j<=m;j++) f[i]=(f[i]-1ll*f[j]*qry(p[i],p[j])%mod+mod)%mod;
    }
    printf("%d\n",f[0]);
    return 0;
}