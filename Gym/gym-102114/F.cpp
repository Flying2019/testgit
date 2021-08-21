#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define mod 1000000007
#define ll long long
#define P pair<ll,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
int p[N],iv[N];
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1)r=1ll*r*a%mod;
    return r;
}
int b[N];
#define S(a) (a.size())
void dfs(int u,int n,vector<P >&res,ll s=0,int c=1)
{
    if(u>n) res.push_back(MP(s,c));
    else dfs(u+1,n,res,s,c),dfs(u+1,n,res,s+p[u],mod-c);
}
vector<P >v1,v2;
int C[N][N],sm[1<<16][N];
int main()
{
    for(int i=1;i<=N-10;i++) iv[i]=ksm(i);
    for(int i=C[0][0]=1;i<=N-10;i++)
        for(int j=C[i][0]=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;ll m=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]),m+=p[i]+1;
        m/=2;
        b[0]=1;
        for(int i=1;i<n;i++)
            for(int j=n-1;~j;j--) b[j]=(1ll*(m-i)%mod*b[j]%mod+(j?mod-b[j-1]:0))%mod;
        int n1=n/2,inv=1;
        for(int i=1;i<n;i++) inv=1ll*inv*iv[i]%mod;
        dfs(1,n1,v1),dfs(n1+1,n,v2);
        sort(v1.begin(),v1.end()),sort(v2.begin(),v2.end());
        for(int i=0;i<S(v2);i++)
        {
            int s=1;
            for(int j=0;j<n;j++,s=1ll*v2[i].fi%mod*s%mod) sm[i][j]=1ll*v2[i].se*s%mod;
            if(!i) continue;
            for(int j=0;j<n;j++) sm[i][j]=(sm[i][j]+sm[i-1][j])%mod;
        }
        int ans=0;
        for(int i=0,u=S(v2)-1;i<S(v1);i++)
        {
            for(;~u && v1[i].fi+v2[u].fi>m-n;u--);
            if(u<0) continue;
            int s=1;
            for(int j=0;j<n;j++,s=1ll*v1[i].fi%mod*s%mod)
                for(int k=j;k<n;k++)
                    ans=(ans+1ll*b[k]*s%mod*sm[u][k-j]%mod*C[k][j]%mod*v1[i].se)%mod;
        }
        printf("%d\n",1ll*ans*inv%mod);
        for(int i=1;i<=n;i++) b[i]=0;
        for(int i=0;i<S(v2);i++) memset(sm[i],0,sizeof(sm[i]));
        v1.clear();v2.clear();
    }
    return 0;
}