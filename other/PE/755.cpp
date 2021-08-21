#include<iostream>
#include<cstdio>
#include<cstring>
#define N 63
#define ll long long
using namespace std;
ll f[N]={1,1},s[N];const ll lim=10000000000000ll;
ll _2[N],ans=0;
void dfs(ll k=lim,int c=62)
{
    if(!c){++ans;return;}
    if(f[c]>k){dfs(k,c-1);return;}
    if(s[c]<=k){ans+=_2[c];return;}
    dfs(k,c-1);dfs(k-f[c],c-1);
}
int main()
{
    _2[0]=1;
    for(int i=1;i<=62;i++) _2[i]=_2[i-1]*2;
    s[1]=1;
    for(int i=2;i<=63;i++) f[i]=f[i-1]+f[i-2],s[i]=s[i-1]+f[i];
    dfs();
    printf("%lld\n",ans);
    return 0;
}