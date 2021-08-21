#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3010
#define M 1000010
using namespace std;
const int B=1000000;
int val[M<<2],tag[M<<2];
void setg(int u,int v){tag[u]+=v;val[u]+=v;}
void push(int u){if(tag[u]) setg(u<<1,tag[u]),setg(u<<1|1,tag[u]),tag[u]=0;}
void change(int u,int l,int r,int p,int v)
{
    if(l==r){val[u]=max(val[u],v);return;}
    int mid=(l+r)>>1;push(u);
    if(p<=mid) change(u<<1,l,mid,p,v);
    else change(u<<1|1,mid+1,r,p,v);
    val[u]=max(val[u<<1],val[u<<1|1]);
}
void insert(int u,int l,int r,int L,int R,int v)
{
    if(L>R || l>R || L>r) return;
    if(L<=l && r<=R){setg(u,v);return;}
    int mid=(l+r)>>1;push(u);
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
    val[u]=max(val[u<<1],val[u<<1|1]);
}
int qry(int u,int l,int r,int L,int R)
{
    if(L>R || l>R || L>r) return 0;
    if(L<=l && r<=R) return val[u];
    int mid=(l+r)>>1;push(u);
    if(R<=mid) return qry(u<<1,l,mid,L,R);
    if(L>mid) return qry(u<<1|1,mid+1,r,L,R);
    return max(qry(u<<1,l,mid,L,R),qry(u<<1|1,mid+1,r,L,R));
}
void clear(int u,int l,int r)
{
    if(!val[u]) return;
    int mid=(l+r)>>1;
    val[u]=tag[u]=0;
    if(l==r) return;
    clear(u<<1,l,mid);clear(u<<1|1,mid+1,r);
}
int l[N],r[N];
struct node{
    int x,y,c;
    node(int X=0,int Y=0,int C=0):x(X),y(Y),c(C){}
    bool operator <(const node a)const{return x==a.x?y>a.y:x>a.x;}
};
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&l[i],&r[i]);
            l[i]--;r[i]--;
            if(l[i]>r[i]) l[i]-=B;
        }
        int res=0;
        for(int i=1;i<=n;i++)
        {
            int c=0;int len=r[i]-l[i]+1;
            vector<node>v;
            for(int j=1;j<=n;j++)
            if(l[j]<=l[i] && r[i]<=r[j]) ++c;
            else if(l[j]<=r[i] && r[j]>=r[i]) v.push_back(node(r[i]-l[j]+1,r[j]-r[i],0));
            else if(l[j]<=l[i] && r[j]>=l[i]) v.push_back(node(len-(r[j]-l[i]+1),max((B-len)-(l[i]-l[j]),0),1));
            else if(l[j]<=l[i]+B && r[j]>=l[i]+B) v.push_back(node(len-(r[j]-(l[i]+B)+1),max((B-len)-((l[i]+B)-l[j]),0),1));
            else if(l[j]+B<=r[i] && r[j]+B>=r[i]) v.push_back(node(r[i]-(l[j]+B)+1,(r[j]+B)-r[i],0));
            sort(v.begin(),v.end());
            for(auto u:v)
            if(u.c==1) change(1,0,B,u.y,qry(1,0,B,0,u.y)),insert(1,0,B,u.y,B,1);
            else insert(1,0,B,0,u.y-1,1);
            c+=qry(1,0,B,0,B);
            // printf("%d ",c);
            res=max(res,c);
            clear(1,0,B);
        }
        printf("%d\n",res);
    }
    return 0;
}