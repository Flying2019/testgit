#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<unordered_set>
#define ll long long
#define N 200010
#define mod 998244353
#define B 2333
using namespace std;
char str[N];
int s[N],n;
int h[N],bs[N];
int get(int l,int r){return (h[r]-1ll*h[l-1]*bs[r-l+1]%mod+mod)%mod;}
int lcp(int x,int y)
{
    int l=1,r=n-max(x,y)+1,res=0;
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
    int l=1,r=min(x,y),res=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid+1;
        else r=mid-1;
    }
    return r;
}
bool cmp(int l1,int l2)//s[l1:]<s[l2:]
{
    int l=lcp(l1,l2);
    return s[l1+l]<s[l2+l];
}
int nxt[N];
int tt,pr[N*20],f[N],sf[N*20];
vector<int>g[N*20];
unordered_set<ll>fd;
void lyndon(bool ell)
{
    for(int i=n-1;i;i--)
        for(nxt[i]=i+1;nxt[i] && cmp(nxt[i],i)==ell;nxt[i]=nxt[nxt[i]]);
}
void make_runs()
{
    for(int k=n-1;k;k--)
    if(nxt[k])
    {
        int dl=lcs(k,nxt[k]),dr=lcp(k,nxt[k]),p=nxt[k]-k;
        int l=k-dl+1,r=nxt[k]+dr-1;
        if(dl+dr<=p || !fd.insert(1ll*r*N+l).second) continue;
        for(int i=l-1;i<l+2*p-1 && i+2*p<=r;i++)
        {
            int x=++tt;pr[x]=p;
            for(int j=i+2*p;j<=r;j+=2*p) g[j].push_back(x);
        }
    }
}
void init()
{
    bs[0]=1;
    for(int i=1;i<=n;i++) h[i]=(1ll*h[i-1]*B+s[i])%mod,bs[i]=1ll*bs[i-1]*B%mod;
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) s[i]=str[i]-'a'+1;
    init();
    lyndon(0);make_runs();
    lyndon(1);make_runs();
    int sm=f[0]=1;
    for(int i=1;i<=n;i++)
    {
        f[i]=sm;
        for(int v:g[i]) f[i]=(f[i]-2ll*(sf[v]=(sf[v]+f[i-2*pr[v]])%mod)%mod+mod)%mod;
        sm=(sm+f[i])%mod;
    }
    printf("%d\n",f[n]);
    return 0;
}