#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int ton[N],c[N],tp;
int a[N],n;
bool add(int x,int k)
{
    while(tp && ton[tp]>x) tp--;
    while(tp && ton[tp]==x && c[tp]==k) tp--,--x;
    if(!x) return false;
    if(!tp || ton[tp]!=x) ton[++tp]=x,c[tp]=2;
    else c[tp]++;
    return true;
}
bool check(int k)
{
    tp=0;bool fi=true;
    for(int i=1;i<=n;i++)
    if(i==1 || a[i]<=a[i-1])
    {
        // for(int j=1;j<=tp;j++) printf("%d,%d ",ton[j],c[j]);puts("");
        if(fi){fi=false;continue;}
        if(!add(a[i],k)) return false;
    }
    return true;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    bool inc=true;
    for(int i=2;i<=n;i++) if(a[i]<=a[i-1]) inc=false;
    if(inc){puts("1");return 0;}
    int l=2,r=n,res=1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,res=mid;
        else l=mid+1;
    }
    printf("%d",res);
    return 0;
}