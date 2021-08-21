#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 250010
#define ll long long
using namespace std;
ll val[N<<2],tag[N<<2];
void setg(int x,ll v){val[x]+=v;tag[x]+=v;}
void push(int u){if(tag[u]) setg(u<<1,tag[u]),setg(u<<1|1,tag[u]),tag[u]=0;}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L<=l && r<=R){setg(u,v);return;}
    int mid=(l+r)>>1;push(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    val[u]=min(val[u<<1],val[u<<1|1]);
}
int a[N],ca[N],b[N],cb[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),ca[i]=a[i]=-a[i];
    for(int i=1;i<=m;i++) scanf("%d",&b[i]),cb[i]=b[i];
    sort(a+1,a+n+1);sort(b+1,b+m+1);
    for(int i=1;i<=n;i++) insert(1,1,n,i,n,a[i]);
    for(int i=1,j=1;i<=n;i++)
    {
        while(j<=m && b[j]<i)j++;
        insert(1,1,n,i,n,m-j+1);
    }
    int q;
    scanf("%d",&q);
    while(q --> 0)
    {
        int op,x;scanf("%d%d",&op,&x);
        if(op==1)
        {
            int v=lower_bound(a+1,a+n+1,ca[x])-a;
            a[v]--;ca[x]--;
            insert(1,1,n,v,n,-1);
        }
        else if(op==2)
        {
            int v=upper_bound(a+1,a+n+1,ca[x])-a-1;
            a[v]++;ca[x]++;
            insert(1,1,n,v,n,1);
        }
        else if(op==3){cb[x]++;if(cb[x]<=n) insert(1,1,n,cb[x],n,1);}
        else{if(cb[x]<=n) insert(1,1,n,cb[x],n,-1);cb[x]--;}
        printf("%d\n",val[1]>=0);
    }
    return 0;
}