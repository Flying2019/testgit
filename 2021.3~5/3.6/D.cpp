#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 2000020
#define mod 1000000007
using namespace std;
int fac[N],inv[N],_2[N];
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
int C(int a,int b){return a<b || a<0 || b<0?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int C(int a,int b,int c){return 1ll*C(a,b)*C(a-b,c)%mod;}
int calc(int a,int b){return C(a+b-1,a-1);}
void init(int n=N-10)
{
    fac[0]=_2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod,_2[i]=2ll*_2[i-1]%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
class LittleElephantAndBoard
{
    public:
    int ans=0;
    void solve(int x,int y,int z,int n)
    {
        for(int i=0;i<=n;i++)
        {
            int y0=(y-z+n-i)>>1,y1=y-y0-i;
            int z0=(z-y+n-i)>>1,z1=z-z0-i;
            if((y-z+n-i)&1 || y0<0 || z0<0 || y1<0 || z1<0 || y1!=z1) continue;
            ans=(ans+1ll*_2[i+1]*C(n,i,y0)%mod*calc(n,y1)%mod)%mod;
        }
    }
    int getNumber(int m,int x,int y,int z)
    {
        init();
        int a=m-x,b=m-y,c=m-z;
        solve(a,b,c,a);solve(a,b,c,a-1);swap(a,b);
        solve(a,b,c,a);solve(a,b,c,a-1);swap(a,c);
        solve(a,b,c,a);solve(a,b,c,a-1);swap(b,c);
        return ans;
    }
};
// LittleElephantAndBoard F;
// int main()
// {
//     cout<<F.getNumber(474,250,300,398);
//     return 0;
// }