#include<iostream>
#include<cstdio>
#include<cstdlib>
#define N 300010
using namespace std;
int a[N],s[N],n;
bool check(int x)
{
    int res=0;
    for(int i=1;i<=n;i+=2) if(res+x<=s[i]) res=min(res,s[i+1]);
    return x+res<=s[n];
}
int c[2];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[i&1]+=a[i];
    if(n%2==0){printf("%d %d\n",max(c[0],c[1]),min(c[0],c[1]));return 0;}
    for(int i=1;i<=n;i++) s[i]=s[i-1]+(i&1?1:-1)*a[i];
    int l=0,r=c[0]+c[1],ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    printf("%d %d\n",c[0]+ans,c[1]-ans);
    return 0;
}