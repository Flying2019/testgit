#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int a[N];
bool vis[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;i++) scanf("%d",&a[i]);
    int ans=0,v0=0,v1=0;
    for(int i=1;i<=n+m;i++)
    if(!vis[i])
    {
        bool c0=i<=n,c1=i>n;
        int c=1;vis[i]=true;
        if(a[i]==i) continue;
        for(int j=a[i];j!=i;j=a[j])
        vis[j]=true,++c,c0|=j<=n,c1|=j>n;
        if(!c0) v0++;
        if(!c1) v1++;
        ans+=c-1;
    }
    int v=min(v0,v1);
    ans+=2*v;v0-=v;v1-=v;
    ans+=2*v0+2*v1;
    printf("%d\n",ans);
    return 0;
}