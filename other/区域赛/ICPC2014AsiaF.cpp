#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 1000010
#define mod 1000000007
using namespace std;
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
int inv[N];
int main()
{
    int t;
    scanf("%d",&t);
    inv[1]=1;
    for(int i=2;i<=N-10;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    for(int _=1;_<=t;_++)
    {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        int ans=0,r=1;
        for(int i=1;i<=k;i++)
        {
            r=1ll*r*(k-i+1)%mod*inv[i]%mod;
            ans=(ans+((k-i)&1?-1ll:1ll)*r*ksm(i-1,n-1)%mod*i%mod+mod)%mod;
        }
        for(int i=1;i<=k;i++) ans=1ll*ans*(m-i+1)%mod*inv[i]%mod;
        printf("Case #%d: %d\n",_,ans);
    }
    return 0;
}