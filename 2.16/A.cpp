#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 998244353
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
int d[N],tot[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int c=0;
        scanf("%d",&c);
        if(i==1 && c!=0){puts("0");return 0;}
        d[c]++;
    }
    if(d[0]!=1){puts("0");return 0;}
    int ans=1;
    for(int i=1;i<=n;i++)
        ans=1ll*ans*ksm(d[i-1],d[i])%mod;
    printf("%d\n",ans);
    return 0;
}