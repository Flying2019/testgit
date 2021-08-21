#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int a[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        int u=1;
        for(int i=1;i<=k;i++)
        {
            while(a[u]==0 && u<=n) u++;
            if(u>n) break;
            a[u]--;a[n]++;
        }
        for(int i=1;i<=n;i++) printf("%d ",a[i]);
        puts("");
    }
    return 0;
}