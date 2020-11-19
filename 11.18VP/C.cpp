#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 998244353
using namespace std;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int ans=1;
    for(int i=1;i<=n+m;i++) ans=2ll*ans%mod;
    printf("%d\n",ans);
    return 0;
}