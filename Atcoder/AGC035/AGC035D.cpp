#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#define ll long long
#define P pair<ll,ll>
#define MP make_pair
#define N 18
using namespace std;
int a[N];
map<P,ll>p[N][N];
ll dfs(int l,int r,ll vl,ll vr)
{
    if(l>=r-1) return 0;
    if(p[l][r].count(MP(vl,vr))) return p[l][r][MP(vl,vr)];
    ll &res=p[l][r][MP(vl,vr)];res=1e16;
    for(int j=l+1;j<r;j++) res=min(res,dfs(l,j,vl,vl+vr)+dfs(j,r,vl+vr,vr)+a[j]*(vl+vr));
    return res;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    printf("%lld\n",dfs(1,n,1,1)+a[1]+a[n]);
    return 0;
}