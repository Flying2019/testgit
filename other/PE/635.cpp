#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100000010
#define mod 1000000009
using namespace std;
int *p,pt;
int *fac,*inv;
bool *pr;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
void init(int n=N-10)
{
    p=new int[N]();
    pr=new bool[N]();
    for(int i=2;i<=n;i++)
    {
        if(!pr[i]) p[++pt]=i;
        for(int j=1;j<=pt && i*p[j]<=n;j++)
        {
            pr[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
    fac=new int[N*3+1](),inv=new int[N*3+1]();
    for(int i=fac[0]=1;i<=N*3;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[N*3]=ksm(fac[N*3]);
    for(int i=N*3-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int A2(int x){return x==2?2:(1ll*(C(2*x,x)-2)*ksm(x)%mod+2+mod)%mod;}
int A3(int x){return x==2?6:(1ll*(C(3*x,x)-3)*ksm(x)%mod+3+mod)%mod;}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    int ans=0;
    for(int i=1;i<=pt && p[i]<=n;i++) ans=(ans+A2(p[i]))%mod;
    for(int i=1;i<=pt && p[i]<=m;i++) ans=(ans+A3(p[i]))%mod;
    printf("%d\n",ans);
    return 0;
}