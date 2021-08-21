#include<iostream>
#include<cstdio>
#include<cstring>
#define N 600010
#define mod 1000000007
using namespace std;
char s[N],t[N];
int ca,cb,cs,all;
int _2[N],n;
int slv(int x){return (2ll*_2[x]%mod-2+mod)%mod;}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
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
int mu[N],p[N],pt,g[N];
bool pr[N];
void init(int n=N-10)
{
    _2[0]=fac[0]=1;
    for(int i=1;i<=n;i++) _2[i]=_2[i-1]*2ll%mod,fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++pt]=i,mu[i]=-1;
        for(int j=1;j<=pt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=true;
            if(i%p[j]==0){mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;i*j<=n;j++) g[i*j]=(g[i*j]+1ll*mu[j]*_2[i]+mod)%mod;
}
int f(int a,int b)
{
    if(a<0) a=-a,b=-b;
    if(b>0) return 0;
    b=-b;
    if(!a && !b) return all;if(!a || !b) return 0;
    int g=gcd(a,b);
    return slv(n/max(a/g,b/g));
}
int main()
{
    scanf("%s%s%d",s+1,t+1,&n);
    int sl=strlen(s+1),sr=strlen(t+1),ans=0;
    init();
    for(int i=1;i<=n;i++) all=(all+1ll*g[i]*(n/i)%mod*(n/i))%mod;
    if(sl==sr)
    {
        int c=1;
        for(int i=1;i<=sl;i++)
        if(s[i]=='?' && t[i]=='?') c=c*2ll%mod;
        else if(s[i]!='?' && t[i]!='?' && s[i]!=t[i]) c=0;
        ans=(ans+1ll*c*slv(n)%mod*slv(n)%mod-1ll*c*all%mod+mod)%mod;
    }
    for(int i=1;i<=sl;i++)
    if(s[i]=='?') cs++,ca++;
    else if(s[i]=='A') ca++;
    else cb++;
    for(int i=1;i<=sr;i++)
    if(t[i]=='?') cs++,cb--;
    else if(t[i]=='A') ca--;
    else cb--;
    for(int i=0;i<=cs;i++)
        ans=(ans+1ll*f(ca-i,cb+i)*C(cs,i)%mod)%mod;
    printf("%d\n",ans);
    return 0;
}