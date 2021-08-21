#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define mod 1000000007
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        int ans=1;
        for(int i=1;i<=k;i++) ans=1ll*ans*n%mod;
        printf("%d\n",ans);
    }
    return 0;
}