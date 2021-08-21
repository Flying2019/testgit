#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define M 14
#define mod 998244353
using namespace std;
int inv[N];
void init(int n=N-10){inv[1]=1;for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;}
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
int main()
{
    int n;
    scanf("%d",&n);
    return 0;
}