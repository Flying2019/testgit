#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define ll long long
using namespace std;
ll g[N*N],f[N][N*N],fac[N];
int id[N*N];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
struct frac{
    ll x,y;
    frac(ll X=0,ll Y=1){ll G=gcd(X,Y);x=X/G;y=Y/G;}
};
frac operator +(frac a,frac b){return frac(a.x*b.y+a.y*b.x,a.y*b.y);}
frac operator -(frac a,frac b){return frac(a.x*b.y-a.y*b.x,a.y*b.y);}
frac operator *(frac a,frac b){return frac(a.x*b.x,a.y*b.y);}
frac operator /(frac a,frac b){return frac(a.x*b.y,a.y*b.x);}
bool operator <(frac a,frac b){return (__int128)a.x*b.y<(__int128)b.x*a.y;}
int x[N];
int main()
{
    for(int n=1;n<N;n++)
    {
        int t=n*(n-1)/2;
        f[n][0]=1;
        for(int i=1;i<=t;i++)
            for(int l=0;l<n && l<=i;l++) f[n][i]+=f[n-1][i-l];
    }
    fac[0]=1;
    for(int n=1;n<N;n++) fac[n]=fac[n-1]*n;
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,d;ll a,b,c;scanf("%d%lld%lld%lld%d",&n,&a,&b,&c,&d);
        int t=n*(n-1)/2;
        for(int i=0;i<=t;i++) g[i]=min(a*i,(t-i)*a+b),id[i]=i;
        sort(id,id+t+1,[&](int x,int y){return g[x]<g[y];});
        frac res(-1);
        for(int i=-1;i<=t;i++)
        {
            ll c1=0,c2=fac[n];
            for(int j=0;j<=i;j++) c1+=f[n][id[j]]*g[id[j]],c2-=f[n][id[j]];
            frac u(c1+c*c2,fac[n]-c2);
            if(res.x==-1 || u<res) res=u;
        }
        res=res+c;
        // printf("%lld/%lld\n",res.x,res.y);
        while(d --> 0)
        {
            for(int i=1;i<=n;i++) scanf("%d",&x[i]);
            int v=0;
            for(int i=1;i<=n;i++)
                for(int j=i+1;j<=n;j++) v+=x[i]>x[j];
            frac p=res;
            if(g[v]<p) printf("%lld/1\n",g[v]);
            else printf("%lld/%lld\n",p.x,p.y);
        }
    }
    return 0;
}