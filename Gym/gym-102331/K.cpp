#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define mod 998244353
using namespace std;
int f[N],s[N],fn;
int find(int x){return x==f[x]?f[x]:find(f[x]);}
int tx[N],ty[N],tp;
bool merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return false;
    if(s[x]>s[y]) swap(x,y);
    s[y]+=s[x];f[x]=y;
    tx[++tp]=x;ty[tp]=y;fn--;
    return true;
}
int _a[N];
void back(int tl){while(tp>tl) f[tx[tp]]=tx[tp],s[ty[tp]]-=s[tx[tp]],tp--,fn++;}
struct border{
    int l,k;
}p[N*N];
bool link(border a){bool can=false;for(int i=0;i<a.k-a.l;i++) can|=merge(a.l+i,a.k+i);return can;}
int tt;
int dfs(int u)
{
    if(u>tt) return _a[fn];
    int tl=tp;
    if(!link(p[u])) return 0;
    int ans=dfs(u+1);back(tl);
    return (dfs(u+1)-ans+mod)%mod;
}
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    _a[0]=1;
    for(int i=1;i<=n;i++) _a[i]=_a[i-1]*35ll%mod;
    for(int j=n/2;j*2>=n-k && j>=1;j--)
        for(int i=1;i<=n;i++)
        if(n-i+1>=j*2) p[++tt]=(border){i,i+j};
    for(int i=1;i<=n;i++) f[i]=i,s[i]=1;fn=n;
    if(tt>200) random_shuffle(p+1,p+tt+1);
    printf("%d\n",dfs(1));
    return 0;
}