#include<iostream>
#include<cstdio>
#include<cstring>
#include<chrono>
#include<random>
#include<ctime>
#define N 200010
#define ll long long
using namespace std;
ll a[N];
mt19937_64 randll(time(0));
int main()
{
    int n;ll mod,k;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) a[i]=(unsigned ll)randll()%1000000000000000000;
    mod=100000000+(unsigned ll)randll()%10000000000;
    k=randll()%mod;
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%lld ",a[i]);puts("");
    for(int i=1;i<=n;i++) printf("%lld ",(a[i]+k)%mod);puts("");
    printf("%lld %lld",mod,k);
    return 0;
}