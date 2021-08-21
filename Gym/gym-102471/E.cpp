#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
#define inf 1000000007
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;ll c[N<<1];
void add(int u,int v,int w)
{
    nxt[++cnt]=head[u];c[cnt]=w;
    to[cnt]=v;head[u]=cnt;
}
int n,dep[N];
void dfs(int u,int p,ll w,vector<int>&len)
{
    len.push_back(w);dep[u]=dep[p]+1;
    if(u==n) return;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==p) continue;
        dfs(v,u,c[i],len);
    }
}
ll sum[N];
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    ll res=0;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);res+=w;
    }
    int q=0;
    for(int i=head[1];i;i=nxt[i])
    {
        vector<int>len;
        dfs(to[i],1,c[i],len);
        sort(len.begin(),len.end());
        for(int j=0;j<dep[n];j++) sum[j]+=len[j];
    }
    ll ans=0;res/=dep[n];
    for(int i=0;i<dep[n];i++)
    {
        if(sum[i]<=res) ans+=res-sum[i];
        else break;
    }
    printf("%lld\n",ans);
    return 0;
}