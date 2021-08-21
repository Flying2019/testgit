#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 1000000007
using namespace std;
class SubRectangles
{
public:
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
    int countWays(int h,int w,int h2,int w2)
    {
        init();
        int n=h2*w2,m=1<<n,ans=0;
        for(int s=0;s<m;s++)
        {
            int r[4]={0,0,0,0},c[4]={0,0,0,0};
            for(int i=0;i<n;i++)
            if((s>>i)&1) r[i/w2]++,c[i%w2]++;
            int res=1;
            for(int i=0;i<w2;i++)
            {
                int t=0;
                for(int j=0;j<=c[i];j++) t=(t+ksm(C(c[i],j),(w-i-1)/w2+1))%mod;
                res=1ll*res*t%mod;
            }
            for(int i=0;i<h2;i++)
            {
                int t=(h-i-1)/h2+1;
                if(r[i]==w2) continue;
                if(r[i]+1==w2){res=0;break;}
                if(r[i]+2==w2){res=1ll*res*(ksm(2,t)+mod-2)%mod;continue;}
                if(r[i]+3==w2){res=1ll*res*((2ll*ksm(3,t)-6ll*ksm(2,t)%mod+6+mod)%mod)%mod;continue;}
                res=1ll*res*((ksm(6,t)+2ll*ksm(4,t)-16ll*ksm(3,t)%mod+24ll*ksm(2,t)%mod-14+mod)%mod)%mod;
            }
            ans=(ans+res)%mod;
        }
        return ans;
    }
};
// int main()
// {
//     SubRectangles F;
//     cout<<F.countWays(123456789,987654321,3,4);
// }