#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define ll long long
using namespace std;
int l[N],r[N];
int v[N],tt,n,m;
ll calc(int L,int R)
{
    ll res=0,s=0;
    for(int i=L;i<=R;i++)
    {
        if(i-m+1>=L) s+=l[i-m+1];
        res+=(s+l[i])*r[i];
    }
    return res;
}
ll ans=0;
void pop()
{
    int t=tt;
    for(;v[t]==v[t-1];t--);
    int x=v[t];
    ans+=calc(t,tt);
    if(tt-t+1<m){tt=t-1;while(tt) pop();return;}
    int b=(tt-t+1)/m;
    static int tl[N],tr[N];
    for(int i=0;i<=b;i++) tl[i]=tr[i]=0;
    for(int i=t;i<=tt;i++) tl[(tt-i+1)/m]+=l[i],tr[(i-t+1)/m]+=r[i];
    tt=t+b-1;
    for(int i=1;i<=b;i++) l[tt-i+1]=tl[i],r[t+i-1]=tr[i];
    for(int i=t;i<=tt;i++) v[i]=x+1;
    ans-=calc(t,tt);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        while(tt && v[tt]<x) pop();
        v[++tt]=x;l[tt]=r[tt]=1;
    }
    while(tt) pop();
    printf("%lld\n",ans);
    return 0;
}