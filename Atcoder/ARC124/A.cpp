#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 998244353
#define N 1010
using namespace std;
int a[N],b[N];
char op[2];
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
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x;scanf("%s%d",op,&x);
        b[x]++;
        if(op[0]=='L')
        {
            for(int j=x+1;j<=n;j++) a[j]++;
        }
        else for(int j=1;j<x;j++) a[j]++;
    }
    int ans=1;
    for(int i=1;i<=n;i++)
    if(b[i]>1 || a[i]==0) ans=0;
    else if(b[i]==0) ans=1ll*ans*a[i]%mod;
    printf("%d\n",ans);
    return 0;
}