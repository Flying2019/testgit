#include<iostream>
#include<cstdio>
#include<cstring>
#define N 20
#define ll long long
#define inf 10000000000000000
using namespace std;
ll f[1<<N],s[1<<N][2];
int main()
{
    int n;
    scanf("%d",&n);
    int m=1<<n;
    for(int _=0;_<=1;_++)
    {
        for(int i=0;i<m;i++) scanf("%lld",&s[i][_]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
            if(!(j>>i&1)) s[j^(1<<i)][_]+=s[j][_];
    }
    f[0]=min(s[0][0],s[0][1]);
    for(int i=1;i<m;i++)
    {
        f[i]=inf;
        for(int j=0;j<n;j++)
        if(i>>j&1) f[i]=min(f[i],min(s[i][0]-s[i^(1<<j)][0],s[i][1]-s[i^(1<<j)][1])+f[i^(1<<j)]);
    }
    printf("%lld\n",f[m-1]);
    return 0;
}