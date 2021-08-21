#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int a[N],f[N][2];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int ans=0;
    for(int i=1;i<=n+1;i++)
    {
        if(a[i]<a[i-1]) f[i][0]=f[i-1][0],f[i][1]=min(f[i-1][1],max(f[i-1][0]+a[i]-a[i-1],0));
        else f[i][0]=f[i-1][0]+a[i]-a[i-1],f[i][1]=min(f[i-1][1]+a[i]-a[i-1],f[i-1][0]);
        if(f[i][0]>a[i]) ans++,f[i][0]=f[i][1],f[i][1]=0;
    }
    printf("%d\n",ans);
    return 0;
}