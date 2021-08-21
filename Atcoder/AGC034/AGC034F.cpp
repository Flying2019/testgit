#include<iostream>
#include<cstdio>
#include<cstring>
#define M 1<<18
#define mod 998244353
using namespace std;
const int inv2=(mod+1)/2;
int f[M],g[M],n,m;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
void fwt(int f[],int op=1)
{
    for(int i=1;i<m;i<<=1)
        for(int j=0;j<m;j+=i<<1)
            for(int k=j;k<j+i;k++)
            {
                int x=f[k],y=f[i+k];
                f[k]=(x+y)%mod;f[i+k]=(x-y+mod)%mod;
                if(op==-1) f[k]=1ll*f[k]*inv2%mod,f[i+k]=1ll*f[i+k]*inv2%mod;
            }
}
int main()
{
    scanf("%d",&n);
    m=1<<n;
    int s=0;
    for(int i=0;i<m;i++) scanf("%d",&g[i]),s=(s+g[i])%mod;
    s=ksm(s);
    for(int i=0;i<m;i++) g[i]=1ll*g[i]*s%mod;
    g[0]--;
    for(int i=1;i<m;i++) f[i]=mod-1;
    f[0]=m-1;
    fwt(f);fwt(g);
    for(int i=0;i<m;i++) f[i]=1ll*f[i]*ksm(g[i])%mod;
    fwt(f,-1);
    for(int i=0;i<m;i++) printf("%d\n",(f[i]-f[0]+mod)%mod);
    return 0;
}