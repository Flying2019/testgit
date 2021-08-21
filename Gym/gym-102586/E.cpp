#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 200010
#define ll long long
using namespace std;
int a[N];
bitset<N>f,g;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        ll n,s;int k;
        scanf("%lld%lld%d",&n,&s,&k);
        int m=0;
        for(int i=1;i<=k;i++) scanf("%d",&a[i]),m=max(m,a[i]);
        f.reset(),f.set(0);
        for(int i=0;i<=60;i++)
        {
            g.reset();
            if(n>>i&1) for(int j=1;j<=k;j++) g^=f<<a[j];
            else g=f;
            f.reset();
            for(int j=0;j<m;j++) f[j]=g[j<<1|(s>>i&1)];
        }
        printf("%d\n",f.test(0));
    }
    return 0;
}