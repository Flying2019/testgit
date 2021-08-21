#include<iostream>
#include<cstdio>
#include<cstring>
#define N 8000010
using namespace std;
namespace NTT{
    const int mod=998244353,G=3,Gi=(mod+1)/G;
    int ksm(int a,int b=mod-2)
    {
        int r=1;
        for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
        return r;
    }
    inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
    inline int dec(int x,int y){return x-y<0?x-y+mod:x-y;}
    int rev[N];
    int get_rev(int n)
    {
        int lim=1,l=0;
        while(lim<=n) lim<<=1,l++;
        for(int i=1;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        return lim;
    }
    void ntt(int f[],int lim,int op=1)
    {
        for(int i=1;i<lim;i++)
        if(i<rev[i]) swap(f[i],f[rev[i]]);
        for(int mid=1;mid<lim;mid<<=1)
        {
            int r=ksm(op==1?G:Gi,(mod-1)/(mid*2));
            for(int i=0;i<lim;i+=mid<<1)
                for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
                {
                    int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                    f[i+j]=add(x,y);f[i+j+mid]=dec(x,y);
                }
        }
        if(op==-1)
        {
            int r=ksm(lim);
            for(int i=0;i<lim;i++) f[i]=1ll*f[i]*r%mod;
        }
    }
    void mul(int f[],int g[],int n)
    {
        int lim=get_rev(n*2);
        ntt(f,lim,1);ntt(g,lim,1);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%mod;
        ntt(f,lim,-1);
    }
}
using NTT::mul;
int a[N],b[N];
int main()
{
    int n;
    scanf("%d",&n);
    int m=2000001;
    for(int i=1,x;i<=n;i++) scanf("%d",&x),a[x]++,b[m-x]++;
    mul(a,b,m);
    for(int i=1;i<=m;i++) a[i]=a[i+m];
    // for(int i=1;i<=m*2;i++) printf("%d ",a[i]);
    // puts("");
    for(int x=1;x<=m;x++)
    {
        bool can=true;
        for(int i=1;i*x<=m;i++) if(a[i*x]) {can=false;break;}
        if(can){printf("%d\n",x);return 0;}
    }
    return 0;
}