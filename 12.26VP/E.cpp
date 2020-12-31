#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
int a[N];
struct seg_tree{
    int t[N<<2];
    void insert(int u,int l,int r,int p,int v)
    {
        if(l==r){t[u]=v;return;}
        int mid=(l+r)>>1;
        if(p<=mid) insert(u<<1,l,mid,p,v);
        else insert(u<<1|1,mid+1,r,p,v);
        t[u]=max(t[u<<1],t[u<<1|1]);
    }
    int answer(int u,int l,int r,int L,int R)
    {
        if(L<=l && r<=R) return t[u];
        int mid=(l+r)>>1;
        if(L>mid) return answer(u<<1|1,mid+1,r,L,R);
        if(R<=mid) return answer(u<<1,l,mid,L,R);
        return max(answer(u<<1|1,mid+1,r,L,R),answer(u<<1,l,mid,L,R));
    }
}o[2];
int v[N],mx[2];
int s[N],n;
bool res[N];
bool check(int p,int w){return w<0?0:o[w&1].answer(1,1,n,p,n)>=w;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1,mx=0;i<=n;i++) v[i]=1+(a[i]>mx),mx=max(mx,a[i]);
    memset(o[1].t,0xcf,sizeof(o[1].t));
    for(int i=n;i;i--)
    {
        for(int _=0;_<=1;_++) mx[_]=o[_].answer(1,1,n,a[i],n);
        for(int _=0;_<=1;_++)
        if(v[i]&1) o[!_].insert(1,1,n,a[i],mx[_]+v[i]);
        else o[_].insert(1,1,n,a[i],mx[_]+v[i]);
    }
    for(int i=n;i;i--) s[i]=s[i+1]+v[i]-1;
    int cx=0,cy=0,mx=0,my=0;
    for(int i=1;i<=n;i++)
    {
        o[0].insert(1,1,n,a[i],0);o[1].insert(1,1,n,a[i],(int)0xcfcfcfcf);
        if(check(my,cx+(a[i]>mx)+s[i+1]-cy) || check(max(mx,a[i]),cy+s[i+1]-(cx+(a[i]>mx))))
            cx+=a[i]>mx,mx=max(mx,a[i]);
        else res[i]=true,cy+=a[i]>my,my=max(my,a[i]);
    }
    if(cx!=cy){puts("-1");return 0;}
    for(int i=1;i<=n;i++) printf("%d",res[i]);
    return 0;
}