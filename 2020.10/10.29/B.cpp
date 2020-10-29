#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#define N 500010
#define ll long long
using namespace std;
ll w[N],v[N];
ll s=1;
priority_queue<ll>q;
int main()
{
    int n;ll x,y;
    scanf("%d%lld%lld",&n,&x,&y);
    for(int i=1;i<=n;i++)
    {
        ll a;
        scanf("%lld",&a);
        v[i]=(a-1)/y;
        w[i]=((a-1)%y)/x+1;
        w[i]-=v[i];v[i]++;
    }
    int r=0;
    for(int i=1;i<=n;i++)
    {
        if(s>=w[i]) q.push(v[i]+w[i]),s-=w[i],r++;
        else if(!q.empty() && v[i]+w[i]<=q.top()) s+=q.top()-w[i],q.pop(),q.push(w[i]+v[i]);
        else s+=v[i];
    }
    printf("%d\n",r);
    return 0;
}