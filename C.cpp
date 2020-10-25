#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define N 1000010
#define ll long long
#define mod 998244353
#define ull unsigned long long
#define B 539
using namespace std;
char s[N];
ull bs[N],hs[N];
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
ull geth(int l,int r){return hs[r]-hs[l-1]*bs[r-l+1];}
int tp;
ull pre[N<<1],suf[N<<1],bpos[N<<1];
ull nxt_rnd(ull a){a^=a<<13;a^=a>>15;a^=a<<17;return a^1919810;}

struct gton{
    #define MX ((1<<21)-1)
    ull ton[MX+5];
    int head[MX+5],nxt[MX+5],val[MX+5],tot;
    int qt[MX+5],qtt;
    int insert(ull x)
    {
        int k=x&MX;
        if(!head[k]) qt[++qtt]=k;
        for(int i=head[k];i;i=nxt[i])
        if(ton[i]==x) return ++val[i];
        nxt[++tot]=head[k];val[tot]=0;
        ton[tot]=x;head[k]=tot;
        return ++val[tot];
    }
    int erase(ull x)
    {
        int k=x&MX;
        for(int i=head[k];i;i=nxt[i])
        if(ton[i]==x) return val[i]--;
        return 0;
    }
    int count(ull x)
    {
        int k=x&MX;
        for(int i=head[k];i;i=nxt[i])
        if(ton[i]==x) return val[i];
        return 0;
    }
    void clear(){for(int i=1;i<=qtt;i++) head[qt[i]]=0;tot=qtt=0;}
}st,mt;
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++)
    inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    bs[0]=1;
    for(int i=1;i<=n;i++) bs[i]=bs[i-1]*B,hs[i]=hs[i-1]*B+(ull)(s[i]-'a'+1);
    int ans=0;
    for(int d=1;d<=n;d++)
    {
        st.clear();mt.clear();
        for(int i=1;i+d-1<=n;i+=d) pre[i]=nxt_rnd(geth(i,i+d-1));
        for(int i=n;i>=d;i-=d) suf[i]=nxt_rnd(geth(i-d+1,i));
        ull hs=0;
        int r=fac[n/d];
        for(int i=1;i+d-1<=n;i+=d)
            r=1ll*r*inv[st.insert(geth(i,i+d-1))]%mod,hs+=pre[i];
        mt.insert(hs);
        ans=(ans+r)%mod;
        if(n%d==0) continue;
        for(int i=n,j=n/d*d;j>=d;i-=d,j-=d)
        {
            hs=hs-pre[j-d+1]+suf[i];
            r=1ll*r*inv[st.insert(geth(i-d+1,i))]%mod*st.erase(geth(j-d+1,j))%mod;
            if(mt.count(hs)) continue;
            mt.insert(hs);ans=(ans+r)%mod;
        }
    }
    printf("%d\n",ans);
    return 0;
}