#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
#define N 100010
#define mod 1019260817
#define ll long long
using namespace std;
const int B=233;
char s[N];int n,h[N],bs[N];
int get(int l,int r){return (h[r]-1ll*h[l-1]*bs[r-l+1]%mod+mod)%mod;}
int lcp(int x,int y)
{
    int l=1,r=n-max(x,y)+1;
    while(l<=r){int mid=(l+r)>>1;if(get(x,x+mid-1)==get(y,y+mid-1)) l=mid+1;else r=mid-1;}
    return r;
}
int lcs(int x,int y)
{
    int l=1,r=min(x,y);
    while(l<=r){int mid=(l+r)>>1;if(get(x-mid+1,x)==get(y-mid+1,y)) l=mid+1;else r=mid-1;}
    return r;
}
bool cmp(int x,int y){int l=lcp(x,y);return s[x+l]<s[y+l];}
bool cmp(int l1,int r1,int l2,int r2){int l=lcp(l1,l2);if(l>min(r1-l1,r2-l2)) return r1-l1<r2-l2;return s[l1+l]<s[l2+l];}
#define P pair<int,int>
#define MP make_pair
int al,ar,ak;
int nxt[N];
void lyndon(bool ell)
{
    for(int i=n-1;i;i--)
        for(nxt[i]=i+1;nxt[i] && cmp(nxt[i],i)==ell;nxt[i]=nxt[nxt[i]]);
}
unordered_set<ll>fd;
void make_runs()
{
    for(int i=n-1;i;i--)
    if(nxt[i])
    {
        int dl=lcs(i,nxt[i]),dr=lcp(i,nxt[i]),p=nxt[i]-i;
        int l=i-dl+1,r=nxt[i]+dr-1,k=(r-l+1)/p;
        if(dl+dr<=p || fd.count(1ll*r*N+l)) continue;
        fd.insert(1ll*r*N+l);
        if(k<ak) continue;
        for(int i=0;i<=r-l+1-k*p;i++)
        if(k>ak || (k==ak && cmp(l+i,l+i+k*p-1,al,ar))) ak=k,al=l+i,ar=l+i+k*p-1;
    }
}
void init(int n=N-10){for(int i=bs[0]=1;i<=n;i++) bs[i]=1ll*bs[i-1]*B%mod;}
int main()
{
    int t;
    scanf("%d",&t);
    init();
    while(t --> 0)
    {
        scanf("%s",s+1);fd.clear();al=ar=ak=1;
        n=strlen(s+1);
        for(int i=2;i<=n;i++) if(s[i]<s[al]) al=ar=i;
        for(int i=1;i<=n;i++) h[i]=(1ll*h[i-1]*B+(s[i]-'a'+1))%mod;
        lyndon(0);make_runs();
        lyndon(1);make_runs();
        for(int i=al;i<=ar;i++) putchar(s[i]);puts("");
    }
    return 0;
}