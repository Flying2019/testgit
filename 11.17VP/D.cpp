#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 300010
#define inf 1e8
using namespace std;
int v[N<<2],a[N],b[N];
void build(int u,int l,int r)
{
    if(l==r){v[u]=a[l];return;}
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    v[u]=min(v[u<<1],v[u<<1|1]);
}
int answer(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R) return v[u];
    int mid=(l+r)>>1,ans=inf;
    if(L<=mid) ans=answer(u<<1,l,mid,L,R);
    if(R>mid) ans=min(ans,answer(u<<1|1,mid+1,r,L,R));
    return ans;
}
void insert(int u,int l,int r,int p)
{
    if(l==r){v[u]=inf;return;}
    int mid=(l+r)>>1;
    if(p<=mid) insert(u<<1,l,mid,p);
    else insert(u<<1|1,mid+1,r,p);
    v[u]=min(v[u<<1],v[u<<1|1]);
}
vector<int>tt[N];
int p[N];
void work(int n)
{
    for(int i=1;i<=n;i++)
    {
        if(p[b[i]]==tt[b[i]].size()){puts("NO");return;}
        if(answer(1,1,n,1,tt[b[i]][p[b[i]]])<b[i]){puts("NO");return;}
        insert(1,1,n,tt[b[i]][p[b[i]]]);
        p[b[i]]++;
    }
    puts("YES");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),tt[a[i]].push_back(i);
        build(1,1,n);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        work(n);
        for(int i=1;i<=n;i++) tt[i].clear(),p[i]=0;
    }
    return 0;
}