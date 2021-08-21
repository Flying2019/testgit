#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
#define mod 1000000007
using namespace std;
char t[N];
int suf[4],nxt[N],s[N],a[N],f[N];
int main()
{
    int n;
    scanf("%d%s",&n,t+1);
    for(int i=1;i<=n;i++) a[i]=t[i]-'A'+1,s[i]=s[i-1]^a[i];
    bool sm=true;
    for(int i=2;i<=n;i++)
    if(a[i]!=a[i-1]) sm=false;
    if(sm){puts("1");return 0;}
    for(int i=0;i<4;i++) suf[i]=n+1;
    for(int i=n;i;i--) nxt[i]=suf[s[i]],suf[s[i]]=i;
    for(int i=1;i<=n;i++)
    {
        f[i]=(f[i]+f[i-1])%mod,f[i+1]=(f[i+1]+f[i])%mod;
        if(s[i]) f[i]++;
        f[nxt[i]]=(f[nxt[i]]-f[i]+mod)%mod;
    }
    printf("%d\n",(f[n]+mod)%mod);
    return 0;
}