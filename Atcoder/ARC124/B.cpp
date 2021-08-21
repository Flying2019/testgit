#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#define N 2010
using namespace std;
int a[N],b[N],c[N];
bool vis[N];
int res[N],tt;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    if(n&1)
    {
        int x=0;
        for(int i=1;i<=n;i++) x^=a[i]^b[i];
        bool d=true;
        for(int i=1;i<=n;i++)
        {
            bool can=false;
            for(int j=1;j<=n;j++)
            if(!vis[j] && (a[i]^b[j])==x){vis[j]=true;can=true;break;}
            if(!can){d=false;break;}
        }
        if(d) printf("1\n%d",x);
        else puts("0");
    }
    else
    {
        sort(b+1,b+n+1);
        for(int i=1;i<=n;i++)
        {
            int x=a[1]^b[i];
            for(int j=1;j<=n;j++) c[j]=a[j]^x;
            sort(c+1,c+n+1);
            bool can=true;
            for(int j=1;j<=n;j++) if(c[j]!=b[j]){can=false;break;}
            if(can) res[++tt]=x;
        }
        sort(res+1,res+tt+1);
        tt=unique(res+1,res+tt+1)-res-1;
        printf("%d\n",tt);
        for(int i=1;i<=tt;i++) printf("%d\n",res[i]);
    }
    return 0;
}