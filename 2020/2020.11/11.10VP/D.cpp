#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
ll a[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    ll mx=0,res=0,ans=0;
    for(int v=1;v<=30;v++,res=0)
        for(int i=1;i<=n;i++)
        {
            res+=a[i];
            if(res<0 || a[i]>v) res=0;
            else ans=max(ans,res-v);
        }
    printf("%lld\n",ans);
    return 0;
}