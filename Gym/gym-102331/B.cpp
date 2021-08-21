#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=300010,M=N*60,D=59,mod=998244353;
typedef long long ll;
ll a[N];
int ch[M][2],val[M];
int root=1,cnt=1;
void insert(ll v,int w)
{
    int u=1;
    for(int i=D;~i;i--)
    {
        int c=v>>i&1;
        if(!ch[u][c]) ch[u][c]=++cnt;
        val[ch[u][c]]=(val[ch[u][c]]+w)%mod;u=ch[u][c];
    }
}
int qry(ll v,ll x)
{
    int w=0,u=1;
    for(int i=D;~i;i--)
    if(!(x>>i&1)) w=(w+val[ch[u][!(v>>i&1)]])%mod,u=ch[u][v>>i&1];
    else u=ch[u][!(v>>i&1)];
    return (w+val[u])%mod;
}
int f[N];ll x;
int main()
{
    int n;
    scanf("%d%lld",&n,&x);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=1;f[i]=(f[i]+qry(a[i],x))%mod;
        insert(a[i],f[i]);
        ans=(ans+f[i])%mod;
    }
    printf("%d\n",ans);
    return 0;
}