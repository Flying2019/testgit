#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 100010
using namespace std;
int a[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    ll ans=0;
    if(n&1)
    {
        ll res=0;
        for(int i=1;i<=n/2+1;i++) res-=a[i]*2;
        for(int i=n/2+2;i<=n;i++) res+=a[i]*2;
        res+=a[n/2]+a[n/2+1];
        for(int i=1;i<=n/2;i++) ans-=a[i]*2;
        for(int i=n/2+1;i<=n;i++) ans+=a[i]*2;
        ans-=a[n/2+1]+a[n/2+2];
        ans=max(ans,res);
    }
    else
    {
        for(int i=1;i<=n/2;i++) ans-=a[i]*2;
        for(int i=n/2+1;i<=n;i++) ans+=a[i]*2;
        ans-=a[n/2+1]-a[n/2];
    }
    printf("%lld\n",ans);
    return 0;
}