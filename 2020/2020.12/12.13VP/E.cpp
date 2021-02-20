#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define mod 1000000007
using namespace std;
int f[N],a[N],nxt[N];
char s[N];
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
int main()
{
    int n,m;
    scanf("%d%d%s",&n,&m,s+1);
    for(int i=1;i<=m;i++) a[i]=s[i]==s[1];nxt[m+1]=m+1;
    for(int i=m;i;i--) nxt[i]=a[i]?nxt[i+1]:i;
    if(nxt[1]==m+1)
    {
        f[0]=1,f[1]=2;
        for(int i=2;i<=n;i++) f[i]=(f[i-1]+f[i-2])%mod;
        if(n==1) puts("1");
        else if(n==2) puts("3");
        else printf("%d\n",(f[n-1]+f[n-3])%mod);
        return 0;
    }
    if(n&1){puts("0");return 0;}
    int t=nxt[1];
    for(int i=1;i<=m;i++)
    if(nxt[i]!=m+1 && !a[i-1] && (nxt[i]-i)%2) t=min(t,nxt[i]-i);
    n=n/2,t=(t+1)/2;
    int v=0;
    for(int i=1;i<=n;i++)
    {
        if(i>t) f[i]=v=(v-f[i-t-1]+mod)%mod;
        else f[i]=(v+i*2)%mod;
        v=(v+f[i])%mod;
    }
    printf("%d\n",f[n]);
    return 0;
}