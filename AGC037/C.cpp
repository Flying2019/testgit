#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 200010
#define ll long long
using namespace std;
struct node{
    int u;ll v;
    node(int U=0,ll V=0):u(U),v(V){}
    bool operator <(const node a)const{return v<a.v;}
};
priority_queue<node>q;
int a[N],b[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&b[i]);
        if(b[i]<a[i]){puts("-1");return 0;}
    }
    ll ans=0;
    for(int i=0;i<n;i++)
    if(a[i]<b[i]) q.push(node(i,b[i]));
    while(!q.empty())
    {
        int u=q.top().u;q.pop();
        int d=b[u]-a[u],m=b[(u-1+n)%n]+b[(u+1)%n];
        if(d && d<m){puts("-1");return 0;}
        d=d/m;ans+=d,b[u]-=d*m;
        if(b[u]>a[u]) q.push(node(u,b[u]));
    }
    printf("%lld\n",ans);
    return 0;
}