#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200010
using namespace std;
int d[N];
bool v[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&d[i]);
        sort(d+1,d+n+1);d[n]++;
        int ans=0;
        for(int i=1;i<=n;i++) ans+=d[i]!=1;
        printf("%d\n",min(ans,n/2));
    }
    return 0;
}