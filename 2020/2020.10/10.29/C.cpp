#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 400010
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
        ll m,s;
        int n,mx=0;
        scanf("%lld%lld%d",&m,&s,&n);
        f.reset(),g.reset();
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(mx,a[i]);
        mx*=2;
        f[0]=1;
        for(int _=0;_<63;_++)
        {
            if((m>>_)&1){for(int j=1;j<=n;j++) g^=(f<<a[j]);f=g;g.reset();}
            for(int j=(s>>_)&1;j<=mx;j+=2) g[j>>1]=f[j];
            f=g,g.reset();
        }
        printf("%d\n",(int)f[0]);
    }
    return 0;
}