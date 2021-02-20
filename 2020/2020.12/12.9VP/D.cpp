#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define ll long long
using namespace std;
int f[N];
int x[N],y[N],op[N];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int main()
{
    int n,k;ll m;
    scanf("%d%lld%d",&n,&m,&k);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=k;i++) scanf("%d%d%d",&x[i],&y[i],&op[i]),x[i]++,y[i]++;
    if(m<n-1){puts("No");return 0;}
    if(m==n-1)
    {
        for(int i=1;i<=n;i++)
        if(op[i]==1){puts("No");return 0;}
        puts("Yes");return 0;
    }
    int c=n;
    for(int i=1;i<=k;i++)
    if(op[i]==0)
    {
        int hx=find(x[i]),hy=find(y[i]);
        if(hx==hy) continue;
        f[hx]=hy,c--;
    }
    for(int i=1;i<=k;i++)
    if(op[i]==1 && find(x[i])==find(y[i])){puts("No");return 0;}
    puts(m>=n && m<=(n-c)+1ll*c*(c-1)/2?"Yes":"No");
    return 0;
}