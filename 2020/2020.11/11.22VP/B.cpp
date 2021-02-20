#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int v[N],n;
void add(int x){for(;x<=n;x+=(x&(-x))) v[x]++;}
int qry(int x){int r=0;for(;x;x-=(x&(-x))) r+=v[x];return r;}
int a[N],p[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),p[a[i]]=i;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        add(p[x]);
        if(qry(p[x])<p[x]) ++ans;
    }
    printf("%d\n",ans);
    return 0;
}