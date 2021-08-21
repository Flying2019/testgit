#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 205
#define M 2005
#define mod 10007
#define S(a) ((int)a.size())
#define R(a) resize(a)
#define pb push_back
#define il inline
using namespace std;
il int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=a*a%mod) if(b&1) r=r*a%mod;
    return r;
}
typedef vector<int> poly;
poly operator +(poly a,poly b){a.R(max(S(a),S(b)));for(int i=0;i<S(b);i++) a[i]=add(a[i],b[i]);return a;}
poly operator -(poly a,poly b){a.R(max(S(a),S(b)));for(int i=0;i<S(b);i++) a[i]=dec(a[i],b[i]);return a;}
poly operator *(const poly &a,const poly &b)
{
    poly c(S(a)+S(b)-1);
    for(int i=0;i<S(a);i++)
        for(int j=0;j<S(b);j++) c[i+j]=add(c[i+j],a[i]*b[j]%mod);
    return c;
}
poly operator %(poly f,const poly &g)
{
    int n=S(f)-1,m=S(g)-1;
    for(int i=n;i>=m;i--)
    if(f[i])
    {
        int v=f[i]*ksm(g[m])%mod;
        for(int j=0;j<=m;j++) f[i-j]=dec(f[i-j],v*g[m-j]%mod);
    }
    f.resize(m);
    return f;
}
poly ksm(poly a,int b,const poly &m)
{
    poly r({1});
    for(;b;b>>=1,a=a*a%m) if(b&1) r=r*a%m;
    return r;
}
namespace BM{
    poly g[M];int d[M];
    int fail[M];
    poly work(poly &f,int n)
    {
        int cnt=0,mn=0;
        for(int i=0;i<=n;i++)
        {
            d[i]=0;
            for(int j=1;j<=S(g[cnt]);j++) d[i]=add(d[i],f[i-j]*g[cnt][j-1]%mod);
            d[i]=dec(d[i],f[i]);
            if(!d[i]) continue;
            fail[cnt]=i;
            if(!cnt){g[++cnt]=poly(i+1);continue;}
            int t=fail[mn],w=d[i]*ksm(d[t])%mod;
            poly c(i-t-1);
            c.pb(w);
            for(int v:g[mn]) c.pb(v*(mod-w)%mod);
            g[cnt+1]=g[cnt]+c;
            if(i-t+S(g[mn])>=S(g[cnt])) mn=cnt;
            ++cnt;
        }
        return g[cnt];
    }
}
using BM::work;
int n,k,m;
char s[N];
namespace dp{
    int f[M][N][N],g[M];
    poly init(int m)
    {
        f[0][1][n]=1;
        for(int i=1;i<=m/2+1;i++)
        {
            g[i]=g[i-1]*26%mod;
            for(int l=1;l<=n;l++)
                for(int r=l;r<=n;r++)
                if(s[l]==s[r])
                {
                    f[i][l][r]=add(f[i][l][r],f[i-1][l][r]*25%mod);
                    if(r-l<2) g[i]=add(g[i],f[i-1][l][r]);
                    else f[i][l+1][r-1]=add(f[i][l+1][r-1],f[i-1][l][r]);
                }
                else
                {
                    f[i][l][r]=add(f[i][l][r],f[i-1][l][r]*24%mod);
                    f[i][l+1][r]=add(f[i][l+1][r],f[i-1][l][r]);
                    f[i][l][r-1]=add(f[i][l][r-1],f[i-1][l][r]);
                }
        }
        poly h(m+1);
        for(int i=1;i<=m;i++)
        if(i&1)
        {
            h[i]=g[i>>1]*26%mod;
            for(int j=1;j<=n;j++) h[i]=add(h[i],f[i>>1][j][j]);
        }
        else h[i]=g[i>>1];
        return h;
    }
}
int main()
{
    scanf("%s",s+1);n=strlen(s+1);
    scanf("%d",&m);m=m+n;
    int mx=6*n+10;
    poly w=dp::init(mx);
    // for(int i=0;i<S(w);i++) printf("%d ",w[i]);puts("");
    auto g=work(w,mx);
    for(int i=0;i<S(g);i++) g[i]=dec(mod,g[i]);
    reverse(g.begin(),g.end());
    g.push_back(1);
    // printf("%d\n",m);
    int ans=0;
    auto f=ksm({0,1},m,g);
    for(int i=0;i<S(g)-1;i++) ans=add(ans,w[i]*f[i]%mod);
    printf("%d\n",ans);
    return 0;
}