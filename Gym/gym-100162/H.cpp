#include<iostream>
#include<cstdio>
#include<cstring>
#define N 20
using namespace std;
int g[1<<N],_2[1<<N],t[N],x[N],f[1<<N];
int main()
{
    for(int i=1;i<1<<N;i++) _2[i]=_2[i>>1]+(i&1);
    int n,T=0;
    while(cin>>n)
    {
        printf("Case %d: ",++T);
        int m=1<<n;
        for(int i=0;i<n;i++) scanf("%d%d",&t[i],&x[i]);
        for(int i=0;i<n;i++) g[1<<i]=t[i];
        for(int i=1;i<m;i++) if(!g[i]) g[i]=g[i&(-i)]+g[i-(i&(-i))];
        for(int s=1;s<m;s++)
        {
            f[s]=s;
            for(int i=0;i<n;i++)
            if(!(s>>i&1) && abs(g[s]/_2[s]-t[i])<=x[i]) f[s]|=1<<i;
        }
        for(int s=1;s<m;s++)
            for(int i=0;i<n;i++)
            if(s>>i&1) f[s]|=f[s^(1<<i)];
        int ans=n;
        for(int i=1;i<m;i++) if(f[i]==m-1) ans=min(ans,_2[i]);
        printf("%d\n",ans);
        for(int i=0;i<m;i++) g[i]=f[i]=0;
    }
    return 0;
}