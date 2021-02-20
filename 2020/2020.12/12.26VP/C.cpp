#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define N 200010
#define ll long long
using namespace std;
struct node{
    ll a,b;
    int c;
    bool operator <(const node d)const{return a<d.a;}
}v[N];
bool vis[N];
int s[N];
int main()
{
    int n,t=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&v[t+1].a,&v[t+2].a);
        v[t+1].b=v[t+2].b=i;
        v[t+1].c=0,v[t+2].c=1;
        t+=2;
    }
    sort(v+1,v+t+1);
    long long res=0;
    bool have=false;
    for(int i=1;i<=n;i++)
    {
        s[v[i].c]++;
        res+=v[i].a;
        if(vis[v[i].b]) have=true;
        else vis[v[i].b]=true;
    }
    if(have || s[0]==n || s[1]==n){printf("%lld\n",res);return 0;}
    res+=v[n+1].a-v[n].a;
    s[v[n].c]--,s[v[n+1].c]++;
    if(s[0]==n || s[1]==n){printf("%lld\n",res);return 0;}
    if(v[n].b==v[n+1].b) res+=min(v[n+2].a-v[n+1].a,v[n].a-v[n-1].a);
    printf("%lld\n",res);
    return 0;
}