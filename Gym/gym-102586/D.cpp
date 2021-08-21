#include<iostream>
#include<cstdio>
#include<cstring>
#define N 70
#define ll long long
#define inf 1e17
using namespace std;
ll f[N][N],n,s,x;
bool check(ll x)
{
    memset(f,0x3f,sizeof(f));
    f[60][0]=1;
    for(int i=60;~i;i--)
        for(int j=0;j<=min(n,64ll);j++)
        if(f[i][j]<=inf)
        {
        }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        scanf("%lld%lld%lld",&n,&s,&x);
        if(s<x || (s-x)&1){printf("-1\n");continue;}
        ll l=0,r=s,res=-1;
        while(l<=r)
        {
            ll mid=(l+r)>>1;
            if(check(mid)) r=mid-1,res=mid;
            else l=mid+1;
        }
    }
    return 0;
}