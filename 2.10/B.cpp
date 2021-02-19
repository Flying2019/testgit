#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100050
#define ll long long
using namespace std;
int c[N],n;
bool work(int x)
{
    ll c0=0;
    for(int i=x;i<n;i++) c0+=c[i];
    ll p=1;
    for(int i=x-1;i>0;i--)
    {
        if(c[i]<p) p=1ll*(p*2-c[i]);
        else if(c[i]>p) c0+=c[i]-p;
        if(p>=1e16) return false;
    }
    return p<=c0+c[0];
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&c[i]);
    int p=-1;
    for(int i=0;i<n;i++)
    if(c[i]==1){if(p==-1) p=i;else p=-2;}
    else if(c[i]) p=-2;
    if(p>=0){printf("%d\n",p==0?1:p);return 0;}
    int l=1,r=n+30,res=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(work(mid)) l=mid+1,res=mid;
        else r=mid-1;
    }
    printf("%d\n",res);
    return 0;
}