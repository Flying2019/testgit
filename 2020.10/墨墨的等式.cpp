#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 500010
#define ll long long
using namespace std;
ll dis[N];
int a[N];
queue<int>q;
int main()
{
    int n,m=N;ll l,r;
    scanf("%d%lld%lld",&n,&l,&r);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),m=min(m,a[i]);
    memset(dis,60,sizeof(dis));
    dis[0]=0;q.push(0);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=1;i<=n;i++)
        if(dis[(u+a[i])%m]>dis[u]+a[i]) dis[(u+a[i])%m]=dis[u]+a[i],q.push((u+a[i])%m);
    }
    ll ans=0;
    for(int i=0;i<m;i++)
    if(dis[i]<=r)
    {
        ll xl=max((l-dis[i]+m-1)/m,0ll),xr=(r-dis[i])/m;
        ans+=xr-xl+1;
    }
    printf("%lld\n",ans);
    return 0;
}