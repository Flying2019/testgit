#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int a[N],c[N][2];
int main()
{
    int t=1;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) c[i][0]=c[i][1]=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[a[i]][i&1]++;
        sort(a+1,a+n+1);
        bool can=true;
        for(int i=1;i<=n;i++)
        if(c[a[i]][i&1]) c[a[i]][i&1]--;
        else can=false;
        for(int i=1;i<=n;i++) printf("%d %d\n",c[a[i]][0],c[a[i]][1]);
        if(can) puts("YES");
        else puts("NO");
    }
    return 0;
}