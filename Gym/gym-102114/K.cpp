#include<iostream>
#include<cstdio>
#include<cstring>
#define N 60
#define ll long long
#define lll __int128
using namespace std;
int c[N+5];ll C[N+5][N+5];
const int len[]={1,2,3,5},w[]={1,15,20,24};
ll mul(ll x,ll y,ll mod){return (lll)x*y%mod;}
ll f[N+5];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;ll mod;
        scanf("%d%lld",&n,&mod);mod*=N;
        memset(c,0,sizeof(c));
        C[0][0]=1;
        for(int i=1;i<=N;i++)
            for(int j=C[i][0]=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        ll ans=0;
        for(int i=1;i<=n;i++) scanf("%d",&c[i]);
        for(int i=0;i<4;i++)
        {
            int s=0;
            for(int j=1;j<=n;j++) s+=(c[j]+len[i]-1)/len[i];
            int m=N/len[i];
            if(s>m) continue;
            memset(f,0,sizeof(f));f[0]=1;
            for(int j=1;j<=n;j++)
                for(int k=m;~k;k--)
                {
                    ll tmp=0;
                    for(int p=(c[j]+len[i]-1)/len[i];p<=k;p++) tmp=(tmp+mul(C[k][p],f[k-p],mod))%mod;
                    f[k]=tmp;
                }
            ans=(ans+f[m]*w[i])%mod;
        }
        printf("%lld\n",ans/N);
    }
    return 0;
}