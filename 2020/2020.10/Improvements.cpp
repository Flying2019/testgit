#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int val[N<<1],n;
void add(int x,int v){for(;x<=n;x+=(x&(-x))) val[x]=max(val[x],v);}
int qry(int x){int v=0;for(;x;x-=(x&(-x))) v=max(v,val[x]);return v;}
int mn[N],mr[N],a[N];
int main()
{
    freopen("improvements.in","r",stdin);
    freopen("improvements.out","w",stdout);
    scanf("%d",&n);
    for(int i=1,r;i<=n;i++) scanf("%d",&r),a[r]=i;
    for(int i=1;i<=n;i++) add(a[i]-1,mn[i]=qry(a[i])+1);
    memset(val,0,sizeof(val));
    int ans=0;
    for(int i=n;i>=1;i--) add(a[i]-1,mr[i]=qry(a[i])+1),ans=max(ans,mr[i]+mn[i]-1);
    printf("%d\n",ans);
    return 0;
}