#include<iostream>
#include<cstdio>
#include<cstring>
#define N 400010
#define mod 998244353
using namespace std;
int f[N],n,a[N],b[N];char s[N];
bool can(int x){return n%x!=0 && 2*n%x==0;}
int main()
{
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++) a[i]=s[i]-'0';
    for(int x=1;x<=2*n;x++)
    if(can(x))
    {
        int m=x/2;
        for(int i=1;i<=x/2;i++) f[x]=(2ll*f[x]+a[i])%mod;
        f[x]=(f[x]+1)%mod;
        for(int i=1,j=0;i<=n;i+=m,j++)
            for(int k=i;k<=i+m-1;k++) b[k]=a[k-i+1]^(j&1);
        for(int i=1;i<=n;i++)
        if(b[i]!=a[i]){if(b[i]>a[i]) f[x]=(f[x]+mod-1)%mod;break;}
    }
    for(int i=1;i<=2*n;i++)
    if(can(i)) for(int j=i*2;j<=2*n;j+=i)
    if(can(j)) f[j]=(f[j]+mod-f[i])%mod;
    int ans=0;
    for(int i=1;i<=2*n;i++) ans=(ans+1ll*f[i]*i)%mod;
    printf("%d\n",ans);
    return 0;
}