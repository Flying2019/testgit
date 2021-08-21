#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
ll a[N],s[N],ss[N],S;
int n,len[N];
ll w0(int l,int r){return l*s[l]-l*s[r]-ss[l]+ss[r];}
ll W(int x,int y)
{
    if(!len[x]) return 0;
    int p=min(abs(x-y),len[x]-1);ll r=S-(s[x+p]-s[x-p-1]);
    return w0(x,x-p-1)+w0(x,x+p)+r*(p+1);
}
struct node{
    int u,v;
    node(int U=0,int V=0):u(U),v(V){}
};
ll ans[N];
bool operator <(const node a,const node b){return a.v<b.v;}
struct Con{
    vector<node>f[N<<2];
    void insert(int u,int l,int r,int L,int R,node v)
    {
        if(L>R) return;
        if(L<=l && r<=R){f[u].push_back(v);return;}
        int mid=(l+r)>>1;
        if(L<=mid) insert(u<<1,l,mid,L,R,v);
        if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    }
    void solve(vector<node>&g,int L,int R,int l,int r)
    {
        if(L>R) return;
        int mid=(L+R)>>1,id=0;ll mx=-1;
        for(int i=l;i<=r;i++)
        if(W(i,g[mid].v)>mx) mx=W(i,g[mid].v),id=i;
        ans[g[mid].u]=max(ans[g[mid].u],mx);
        solve(g,L,mid-1,l,id);solve(g,mid+1,R,id,r);
    }
    void dfs(int u,int l,int r)
    {
        sort(f[u].begin(),f[u].end());
        solve(f[u],0,(int)f[u].size()-1,l,r);
        if(l==r) return;
        int mid=(l+r)>>1;
        dfs(u<<1,l,mid);dfs(u<<1|1,mid+1,r);
    }
}T[2];
int main()
{
    scanf("%d%lld",&n,&S);
    a[0]=a[n+1]=s[0]=S;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n+1;i++) s[i]=s[i-1]+a[i],ss[i]=ss[i-1]+a[i]*i;
    for(int i=1;i<=n;i++)
    {
        len[i]=i;
        int l=0,r=min(n-i+1,i-1);
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(s[i+mid]-s[i-mid-1]>=S) r=mid-1,len[i]=mid;
            else l=mid+1;
        }
    }
    // for(int i=1;i<=n;i++) printf("%d ",len[i]);puts("");
    int q;scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        int l,r;scanf("%d%d",&l,&r);
        int mid=(l+r)>>1;
        // for(int j=l;j<=mid;j++) ans[i]=max(ans[i],W(j,l));
        // for(int j=mid+1;j<=r;j++) ans[i]=max(ans[i],W(j,r));
        T[0].insert(1,1,n,l,mid,node(i,l));
        T[1].insert(1,1,n,mid+1,r,node(i,r));
    }
    T[0].dfs(1,1,n);T[1].dfs(1,1,n);
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    return 0;
}