#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 100010
using namespace std;
int a[N];
double b[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) b[i]=1.0/pow(a[i],1.0/(n-1));
    double m=n-1,ans=0;
    for(int i=1;i<=n;i++) ans+=a[i];
    for(int i=1;i<=n;i++)
    {
        double s=1e-10;
        for(int j=i;j<=n;j++) s+=b[j];
        double p=min(1.0,m*b[i]/s);
        ans-=a[i]*pow(p,n);m-=p;
    }
    printf("%.10lf",ans/n);
    return 0;
}