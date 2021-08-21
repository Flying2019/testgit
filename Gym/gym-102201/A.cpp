#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
long long a,b;
int ans[N],tt;
int main()
{
    scanf("%lld%lld",&a,&b);
    while(a!=b)
    {
        while(b%2==0) ans[++tt]=1,b/=2;
        while(a%2==0) ans[++tt]=2,a/=2;
        if(a==b) break;
        if(a>b) ans[++tt]=3,ans[++tt]=2,a=(a+b)/2;
        else ans[++tt]=4,ans[++tt]=1,b=(a+b)/2;
    }
    printf("%d\n",tt);
    for(int i=1;i<=tt;i++)
    if(ans[i]==1) puts("A+=A");
    else if(ans[i]==2) puts("B+=B");
    else if(ans[i]==3) puts("A+=B");
    else puts("B+=A");
    return 0;
}