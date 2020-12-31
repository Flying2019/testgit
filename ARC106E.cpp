#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=19,M=1<<N,K=5000010;
int _2[M],f[M],t[K];
int a[N],n,m,k;
bool check(int x)
{
    for(int i=0;i<m;i++) f[i]=0;f[m]=x;
    for(int i=1;i<=x;i++) f[t[i]^m]--;
    for(int t=1;t<=m;t<<=1)
        for(int s=0;s<=m;s++) if(s&t) f[s^t]+=f[s];
    for(int i=0;i<=m;i++)
        if(1ll*_2[i]*k>f[i]) return false;
    return true;
}
int main()
{
    scanf("%d%d",&n,&k);
    m=(1<<n)-1;
    for(int i=0;i<=m;i++) _2[i]=_2[i>>1]+(i&1);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    int maxn=2*n*k;
    for(int i=1;i<=maxn;i++)
        for(int j=0;j<n;j++)
        if((i-1)%(a[j]*2)<a[j]) t[i]|=1<<j;
    int ans=1e9,l=1,r=maxn;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}