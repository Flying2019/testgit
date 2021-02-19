#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
int a[N],b[N];
#define B 233
#define BL (N/B+3)
int bl[N],n;
struct node{
    int l,r,id;
    node(int L=0,int R=0,int I=0):l(L),r(R),id(I){}
    bool operator <(const node a)const{return bl[l]!=bl[a.l]?bl[l]<bl[a.l]:(bl[l]&1?r>a.r:r<a.r);}
}q[N];
int ans[N];
struct array{
    int b[N];
    void ins(int x,int v){for(;x<=n;x+=(x&(-x))) b[x]+=v;}
    int qry(int x){int r=0;for(;x;x-=(x&(-x))) r+=b[x];return r;}
}f,s;
int res=0;
void addt(int x){s.ins(n-x+1,1);++x;res+=s.qry(n-x+1);}
void addh(int x){f.ins(x,1);--x;res+=f.qry(x);}
void delt(int x){s.ins(n-x+1,-1);++x;res-=s.qry(n-x+1);}
void delh(int x){f.ins(x,-1);--x;res-=f.qry(x);}
int main()
{
    int m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),bl[i]=i/B,b[i]=a[i];
    sort(b+1,b+n+1);
    int p=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+p+1,a[i])-b;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
    sort(q+1,q+m+1);
    int l=1,r=0;
    for(int i=1;i<=m;i++)
    {
        while(r<q[i].r) addt(a[++r]);
        while(l>q[i].l) addh(a[--l]);
        while(r>q[i].r) delt(a[r--]);
        while(l<q[i].l) delh(a[l++]);
        ans[q[i].id]=res;
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}