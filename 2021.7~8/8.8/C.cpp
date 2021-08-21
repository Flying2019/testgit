#include<iostream>
#include<cstdio>
#include<cstring>
#define N 3010
using namespace std;
int f[N],g[N],a[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++) f[i]=g[i]=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        f[1]=g[1]=1;
        for(int i=1;i<=n;i++) f[i];
    }
    return 0;
}