#include<iostream>
#include<cstdio>
#include<cstring>
#define N 4000010
#define M 26
#define mod 998244353
using namespace std;
int ksm(int a,int b=mod-2,int r=1){for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;return r;}
int fac[N],inv[N],_2[N];
void init(int n=N-10)
{
    fac[0]=inv[0]=_2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod,_2[i]=_2[i-1]*2%mod;
    inv[n]=ksm(fac[n]);
    for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int a,int b){return a<0 || b<0 || a<b?0:1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;}
int c[8];
/*
0:-1  1:-1/2  2:0  3:1/2  4:1  5:*  6:↑  7:↓
*/
int s[N];
void prework(int n)
{
    memset(c,0,sizeof(c));
    string s;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>s>>x;
        if(s=="_RLLR" || s=="_RLRL" || s=="R_RLL") c[0]+=x;
        else if(s=="LR_RL") c[1]+=x;
        else if(s=="RL_LR") c[3]+=x;
        else if(s=="LRRL_" || s=="RLRL_" || s=="RRL_L") c[4]+=x;
        else if(s=="LRL_R" || s=="L_RLR" || s=="LL_RR") c[5]+=x;
        else if(s=="L_LRR") c[6]+=x;
        else if(s=="LLR_R") c[7]+=x;
        else c[2]+=x;
    }
}
int main()
{
    init();
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T,id;
    cin>>id>>T;
    while(T --> 0)
    {
        int n;
        cin>>n;
        prework(n);
        int m=c[1]+c[3],m1=c[0]+c[4];
        for(int i=s[0]=1;i<=m;i++) s[i]=(s[i-1]+C(m,i))%mod;
        int res1=0,res2=0,res3=0;
        for(int i=0;i<=m1;i++)
        {
            int t=C(m1,i),t2=2*(c[0]-i)+c[1];
            res2=(res2+1ll*t*C(m,t2))%mod;
            if(t2>0) res1=(res1+1ll*t*s[min(t2-1,m)])%mod;
            if(t2<=m) res3=(res3+1ll*t*(s[m]-(t2<0?0:s[t2])+mod))%mod;
        }
        // printf("%d %d %d\n",res1,res2,res3);
        m=c[7];
        int t0=0,t1=0,t2=0,t3=0,t4=0;
        for(int i=s[0]=1;i<=m;i++) s[i]=(s[i-1]+C(m,i))%mod;
        for(int i=0;i<=c[6];i++)
        {
            int t=C(c[6],i);
            t2=(t2+1ll*t*C(m,i+1))%mod;
            t3=(t3+1ll*t*C(m,i))%mod;
            t4=(t4+1ll*t*C(m,i-1))%mod;
            if(i>=2) t0=(t0+1ll*t*s[min(i-2,m)])%mod;
            if(i<=m-2) t1=(t1+1ll*t*(s[m]-s[i+1]+mod))%mod;
        }
        // printf("%d %d %d\n",t2,t3,res2);
        int r0=(t0+t4)%mod,r1=(t1+t2)%mod,r2=0,r3=t3;
        if(c[5])
        {
            r0=1ll*(r0+t0)*_2[c[5]-1]%mod;
            r1=1ll*(r1+t1)*_2[c[5]-1]%mod;
            r2=(r2+1ll*t2+t3+t4)*_2[c[5]-1]%mod;
            r3=1ll*r3*_2[c[5]-1]%mod;
        }
        t2=1ll*res2*_2[c[2]]%mod;
        t1=1ll*res1*_2[c[2]+c[5]+c[6]+c[7]]%mod,t0=1ll*res3*_2[c[2]+c[5]+c[6]+c[7]]%mod;
        // printf("%d %d %d\n",r3,t2,c[2]);
        cout<<(1ll*r0*t2+t0)%mod<<" "<<(1ll*r1*t2+t1)%mod<<" "<<1ll*r2*t2%mod<<" "<<1ll*r3*t2%mod<<"\n";
    }
    return 0;
}