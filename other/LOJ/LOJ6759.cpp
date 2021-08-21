#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=9000,M=24,mod=1019260817;
typedef long long ll;
int n,m,q;
int ksm(int a,int b=mod-2)
{
    int r=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) r=1ll*r*a%mod;
    return r;
}
struct matr{
    int a[M][M];
    matr(){memset(a,0,sizeof(a));}
    int* operator [](int x){return a[x];}
};
void mul(matr &a,matr &b,matr &c)
{
    memset(&c,0,sizeof(c));
    for(int i=0;i<m;i++)
        for(int k=0;k<m;k++)
            for(int j=0;j<m;j++) c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
}
int matr_rank(matr &a)
{
    matr b;int rnk=0;
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        if(a[i][j])
        {
            if(!b[j][j])
            {
                ll iv=ksm(a[i][j]);++rnk;
                for(int k=j;k<m;k++) b[j][k]=iv*a[i][k]%mod;break;
            }
            ll u=mod-a[i][j];
            for(int k=j;k<m;k++) a[i][k]=(a[i][k]+u*b[j][k])%mod;
        }
    return rnk;
}
matr val[N<<2];
char s[N];
int rand0(){return (1ll*rand()<<30^rand())%(mod-1)+1;}
void build(int u,int l,int r)
{
    if(l==r)
    {
        for(int i=0;i<m;i++)
        {
            scanf("%s",s);
            for(int j=0;j<m;j++) if(s[j]=='1') val[u][i][j]=rand0();
        }
        return;
    }
    int mid=(l+r)>>1;
    build(u<<1,l,mid);build(u<<1|1,mid+1,r);
    mul(val[u<<1],val[u<<1|1],val[u]);
}
void insert(int u,int l,int r,int p,int x,int y)
{
    if(l==r){if(val[u][x][y]) val[u][x][y]=0;else val[u][x][y]=rand0();return;}
    int mid=(l+r)>>1;
    if(p<=mid) insert(u<<1,l,mid,p,x,y);
    else insert(u<<1|1,mid+1,r,p,x,y);
    mul(val[u<<1],val[u<<1|1],val[u]);
}
matr ans;
void qry(int u,int l,int r,int L,int R)
{
    if(L<=l && r<=R){matr c=ans;mul(c,val[u],ans);return;}
    int mid=(l+r)>>1;
    if(L<=mid) qry(u<<1,l,mid,L,R);
    if(R>mid) qry(u<<1|1,mid+1,r,L,R);
}
char opt[3];
char sx[N],sy[N];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    --n;build(1,1,n);
    while(q --> 0)
    {
        int x,y,z;
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='T') scanf("%d",&z),insert(1,1,n,x,y-1,z-1);
        else{
            scanf("%s%s",sx,sy);--y;
            for(int i=0;i<m;i++)
                for(int j=0;j<m;j++) ans[i][j]=i==j;
            qry(1,1,n,x,y);
            for(int i=0;i<m;i++)
                for(int j=0;j<m;j++)
                if(sx[i]=='0' || sy[j]=='0') ans[i][j]=0;
            printf("%d\n",matr_rank(ans));
        }
    }
    return 0;
}