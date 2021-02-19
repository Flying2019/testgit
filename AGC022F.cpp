#include<iostream>
#include<cstdio>
#include<cstring>
#define N 110
#define mod 1000000007
using namespace std;
int fac[N],inv[N];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1)
    {
        if(b&1) r=1ll*r*a%mod;
        a=1ll*a*a%mod;
    }
    return r;
}
int C(int a,int b){return a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int f[N][N];
int main()
{
    int n;
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    f[1][1]=f[1][0]=n;
    for(int i=1;i<n;i++)
        for(int j=1;j<=n-i;j++)
            for(int k=0;k<=j;k++)
            if((j-k)%2==0)
            {
                int x=(j-k)>>1;
                for(int p=0;p<=j;p++)
                {
                    int d=x>p?x-p:p-x;
                    f[i+j][d]=(f[i+j][d]+1ll*f[i][k]*C(n-i,j)%mod*C(j,p))%mod;
                }
            }
    printf("%d\n",f[n][0]);
    return 0;
}