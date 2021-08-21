#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    long long ans=0;
    for(int m=2;m<=n;m++)
    {
        int t=n/(m-1);
        int y=n-t*(m-1),x=m-1-y;
        long long res=1ll*x*t*(t-1)/2+1ll*y*(t+1)*t/2;
        // printf("%lld\n",res);
        ans+=res;
    }
    printf("%lld\n",ans);
    return 0;
}