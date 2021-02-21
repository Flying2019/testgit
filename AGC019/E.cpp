#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10010
#define M 5010
#define mod 998244353
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
void init(int n=N-10)
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
char s[N],t[N];
int s1,s2;
int f[M][N];
int main()
{
    scanf("%s%s",s+1,t+1);
    int n=strlen(s+1);
    init();
    for(int i=1;i<=n;i++)
    if(s[i]==t[i]) s1+=s[i]=='1';
    else s2+=s[i]=='1';
    for(int i=0;i<=s2;i++) f[i][0]=1ll*fac[i]*fac[i]%mod;
    for(int i=1;i<=s2;i++)
        for(int j=1;j<=s1;j++)
        f[i][j]=(1ll*f[i][j-1]*i%mod*j%mod+1ll*f[i-1][j]*i%mod*i%mod)%mod;
    int ans=0;
    for(int i=0;i<=s1;i++) ans=(ans+1ll*f[s2][s1-i]*fac[i]%mod*fac[i]%mod*C(s1,i)%mod*C(s1+s2,i)%mod)%mod;
    printf("%d\n",ans);
    return 0;
}