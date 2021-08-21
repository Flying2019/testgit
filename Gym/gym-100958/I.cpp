#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#define N 110
#define mod 1000000007
using namespace std;
typedef long long ll;
int n,m,a,_a[N];
bool pr[N];
int f[N],g[N],ans;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int G[N][N];
map<ll,int>s;
void dfs(int t)
{
    if(t==0)
    {
        ll u=0;
        for(int i=1;i<m;i++) if(pr[m-i]) u|=1ll<<i;
        s[u]++;return;
    }
    dfs(t-1);
    if(pr[t]) return;
    pr[t]=true;
    vector<int>v;
    for(int i=1;i<m;i++) if(pr[i] && i+t-G[i][t]<=n && !pr[G[i][t]]) v.push_back(G[i][t]);
    for(int u:v) pr[u]=true;
    dfs(t-1);
    for(int u:v) pr[u]=false;
}
int main()
{
    scanf("%d%d%d",&n,&m,&a);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) G[i][j]=gcd(i,j);
    for(int i=_a[0]=1;i<=n;i++) _a[i]=1ll*_a[i-1]*a%mod;
    dfs(m-1);
        int res=0;
        for(int i=m;i<=n;i++)
        {
            f[i]=_a[i];
            for(int j=0;m+j<=i;j++) f[i]=(f[i]-1ll*f[j]*_a[i-j]%mod+mod)%mod;
            for(int j=1;j<m;j++) if(pr[m-j]) f[i]=(f[i]-f[i-j])%mod;
            res=(res+1ll*f[i]*_a[n-i])%mod;
        }
        ans=(ans+res)%mod;
    printf("%d\n",ans);
    return 0;
}