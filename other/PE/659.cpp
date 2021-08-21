#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 20000010
#define ll long long
using namespace std;
ll mod;
namespace er{
    ll W,W0;
    struct xu{
        ll x,y;//shi/xu
        xu(ll R=0,ll W=0):x(R),y(W){}
        xu operator *(const xu a)const{return xu((x*a.x+y*a.y%mod*W)%mod,(x*a.y+y*a.x)%mod);}
    };
    ll ksm(ll a,ll b)
    {
        if(b==0) return 1;if(b==1) return a;
        ll q=ksm(a,b>>1);
        if(b&1) return q*q%mod*a%mod;
        else return q*q%mod;
    }
    xu ksm(xu a,ll b)
    {
        if(b==0) return 1;if(b==1) return a;
        xu q=ksm(a,b>>1);
        if(b&1) return q*q*a;
        else return q*q;
    }
    xu Cipolla(ll x)
    {
        W=W0=0;
        if(ksm(x,(mod-1)>>1)==mod-1) return xu(-1,-1);
        srand(x);
        do
        {
            W0=rand()%mod;
            W=(W0*W0%mod-x+mod)%mod;
        }while(ksm(W,(mod-1)>>1)!=mod-1);
        xu res=ksm(xu(W0,1),(mod+1)>>1);
        res.y=mod-res.x;
        if(res.x>res.y) swap(res.x,res.y);
        return res;
    }
}
int *p,pt;
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
    long long ans=0;
    for(int i=1;p[i]<=2000000;i++) ans+=p[i];
    printf("%lld\n",ans);
}
vector<int> *fac;
int main()
{
    init();
    int n;
    scanf("%d",&n);
    fac=new vector<int>[N];
    for(int i=1;i<=pt;i++)
    {
        int u=p[i];mod=u;
        // printf("run %d\n",u);
        auto r=er::Cipolla(u-1);
        // printf("solve %lld %lld\n",r.x,r.y);
        if(r.x<0) continue;
        for(int j=1;u*j<=N-10;j++)
        if((u*j+r.x)%2==0) fac[(u*j+r.x)/2].push_back(u);
        for(int j=1;u*j<=N-10;j++)
        if((u*j+r.y)%2==0) fac[(u*j+r.y)/2].push_back(u);
    }
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        long long w=4ll*i*i+1,res=0;
        // printf("%lld: ",w);
        for(int v:fac[i]) if(w%v==0)
        {
            res=max(res,(ll)v);
            while(w%v==0) w/=v;
        }
        res=max(res,w);
        // printf("%lld\n",res);
        ans=(ans+res)%1000000000000000000;
    }
    printf("%lld\n",ans);
    return 0;
}