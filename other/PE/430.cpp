#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define N 100010
using namespace std;
long long n;int m;
long double C[4010][4010];
int main()
{
    scanf("%lld%d",&n,&m);
    long double ans=0;
    for(int i=C[0][0]=1;i<=m;i++)
        for(int j=C[i][0]=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    for(int i=1;i<=n;i++)
    {
        long double p=(2.0L*i*(n-i+1)-1)/n/n,s1=1,s2=pow(1-p,m);
        for(int j=0;j<=m/2;j++) ans+=C[m][2*j]*s1*s2,s1*=p*p,s2/=p*p;
    }
    cout<<ans;
    return 0;
}