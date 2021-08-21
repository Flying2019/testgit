#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
#include<vector>
#define N 200010
#define M N*20
using namespace std;
typedef long long ll;
char s[N];
int n,tt;
vector<int>pos[N];
int w[M],wx[M],f[N],len[M];
namespace runs{
    const int B=2333,mod1=1019260817,mod2=1000000009;
    struct P{
        int x,y;
        P(int X,int Y):x(X),y(Y){}
        P(int X=0):x(X),y(X){}
    }hs[N],bs[N];
    P operator +(P a,P b){return P((a.x+b.x)%mod1,(a.y+b.y)%mod2);}
    P operator -(P a,P b){return P((a.x-b.x+mod1)%mod1,(a.y-b.y+mod2)%mod2);}
    P operator *(P a,P b){return P(1ll*a.x*b.x%mod1,1ll*a.y*b.y%mod2);}
    bool operator ==(P a,P b){return a.x==b.x && a.y==b.y;}
    P get(int l,int r){return hs[r]-hs[l-1]*bs[r-l+1];}
    void init()
    {
        bs[0]=1;
        for(int i=1;i<=n;i++) hs[i]=hs[i-1]*B+P(s[i]-'a'+1),bs[i]=bs[i-1]*B;
    }
    int lcp(int x,int y)
    {
        int l=1,r=n-max(x,y)+1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(get(x,x+mid-1)==get(y,y+mid-1)) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
    int lcs(int x,int y)
    {
        int l=1,r=min(x,y);
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
    bool cmp(int l1,int l2){int l=lcp(l1,l2);return s[l1+l]<s[l2+l];}
    int nxt[N];
    unordered_set<ll>st;
    void lyndon(bool ell)
    {
        nxt[n]=0;
        for(int i=n-1;i;i--)
        {
            nxt[i]=i+1;
            for(;nxt[i] && cmp(nxt[i],i)==ell;nxt[i]=nxt[nxt[i]]);
        }
    }
    void make_runs()
    {
        for(int k=n-1;k;k--)
        if(nxt[k])
        {
            int dl=lcs(k,nxt[k]),dr=lcp(k,nxt[k]),p=nxt[k]-k;
            int l=k-dl+1,r=nxt[k]+dr-1;
            if(dl+dr<=p || st.count(1ll*r*N+l)) continue;
            st.insert(1ll*r*N+l);
            for(int i=l-1;i<l+p-1 && i+2*p<=r;i++)
            {
                int x=++tt;
                len[x]=p;
                for(int j=0;i+j<=r;j+=p) pos[i+j].push_back(x);
            }
        }
    }
    void make()
    {
        init();
        lyndon(0);make_runs();
        lyndon(1);make_runs();
    }
}
const int mod=1000000007;
void clear()
{
    for(int i=0;i<=n;i++) pos[i].clear(),f[i]=runs::nxt[i]=0;
    for(int i=1;i<=tt;i++) w[i]=wx[i]=len[i]=0;
    runs::st.clear();tt=0;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        runs::make();
        int sm=0,sw=0;
        f[0]=1;
        for(int i=0;i<=n;i++)
        {
            f[i]+=sw;
            for(int u:pos[i]) f[i]=((f[i]+w[u])%mod+mod-wx[u])%mod;
            sm=(sm+f[i])%mod;
            sw=(sw+sm)%mod;
            for(int u:pos[i]) w[u]=(w[u]+1ll*f[i]*len[u])%mod,wx[u]=(wx[u]+w[u])%mod;
        }
        printf("%d\n",f[n]);
        clear();
    }
    return 0;
}