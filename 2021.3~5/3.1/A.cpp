#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10
#define ll long long
using namespace std;
ll mul(ll a,ll b,ll mod){return a*b%mod;}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll g=exgcd(b,a%b,x,y);
    ll z=x;
    x=y,y=z-a/b*y;
    return g;
}
ll a[N],b[N];
ll excrt(int n)
{
    ll x=a[1],ans=b[1];
    for(int i=2;i<=n;i++)
    {
        ll y=(b[i]-ans%a[i]+a[i])%a[i];
        ll px=0,py=0;
        ll g=exgcd(x,a[i],px,py);
        if(y%g) return -1;
        px=mul(px,y/g,a[i]/g);
        ans+=x*px;
        x=a[i]/g*x;
        ans=(ans%x+x)%x;
    }
    return (ans%x+x)%x;
}
int main()
{
    int n,m,x,y,vx,vy;
    scanf("%d%d%d%d%d%d",&n,&m,&x,&y,&vx,&vy);
    if(vx==0)
    {
        if(x!=0 && x!=n){puts("-1");return 0;}
        printf("%d %d\n",x,vy==1?m:0);
        return 0;
    }
    if(vy==0)
    {
        if(y!=0 && y!=m){puts("-1");return 0;}
        printf("%d %d\n",vx==1?n:0,y);
        return 0;
    }
    int dx=x,dy=y;
    if(vy>=0) dy=m-y;
    if(vx>=0) dx=n-x;
    b[1]=dx;a[1]=n;
    b[2]=dy;a[2]=m;
    ll t=excrt(2);
    if(t==-1) puts("-1");
    else
    {
        ll nx=x+t*vx,my=y+t*vy;
        printf("%lld %lld\n",(nx%(2*n)+2*n)%(2*n),(my%(2*m)+2*m)%(2*m));
    }
    return 0;
}