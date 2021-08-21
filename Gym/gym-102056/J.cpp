#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char s[N];
int sa[N],rk[N],id[N];
int b[N];
int *F=rk,*G=id;
void SA_(int n,int m)
{
    for(int i=0;i<=m;i++) b[i]=0;
    for(int i=1;i<=n;i++) b[F[i]]++;
    for(int i=1;i<=m;i++) b[i]+=b[i-1];
    for(int i=n;i>=1;i--) sa[b[F[G[i]]]--]=G[i];
}
void SA(int n)
{
    int m=27;
    for(int i=1;i<=n;i++) F[i]=s[i]-'a'+1,G[i]=i;
    SA_(n,m);int t=0;
    for(int p=1;p<n;m=t,t=0,p<<=1)
    {
        for(int i=1;i<=p;i++) G[++t]=n-p+i;
        for(int i=1;i<=n;i++) if(sa[i]>p) G[++t]=sa[i]-p;
        SA_(n,m); swap(G,F); F[sa[1]]=t=1;
        for(int i=2;i<=n;i++) F[sa[i]]=(t+=G[sa[i-1]]!=G[sa[i]] || G[sa[i-1]+p]!=G[sa[i]+p]);
    }
}
int ht[N],sum[N];
int f[21][N],_2[N];
int n;
void clear()
{
    for(int i=1;i<=n;i++) sum[i]=ht[i]=sa[i]=rk[i]=id[i]=0;
    for(int i=0;i<=20;i++) memset(f[i],0,sizeof(int)*(n+1));
}
void get_ht(int n)
{
    for(int i=1,p=0;i<=n;ht[F[i]]=p,i++)
    if(F[i]!=1) for(p=p-!!p;i+p<=n && sa[F[i]-1]+p<=n && s[i+p]==s[sa[F[i]-1]+p];p++);
    else ht[F[i]]=0;
    for(int i=1;i<=n;i++) f[0][i]=i;
    for(int i=1,p=2;p<=n;i++,p<<=1)
        for(int j=1;j+p-1<=n;j++)
            if(ht[f[i-1][j]]<ht[f[i-1][j+p/2]]) f[i][j]=f[i-1][j];
            else f[i][j]=f[i-1][j+p/2];
}
int get_min(int l,int r)
{
    int p=_2[r-l+1],x=f[p][l],y=f[p][r-(1<<p)+1];
    return ht[x]<ht[y]?x:y;
}
#define db double
double answer(int l,int r)
{
    if(l==r) return n-sa[r]+1;
    int x=get_min(l+1,r),y=ht[x];
    db fl=answer(l,x-1),fr=answer(x,r),p=1.0*(fr-y)/(fl+fr-2*y);
    return fl*p+y*(1-p);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=2;i<=n;i++) _2[i]=_2[i>>1]+1;
        SA(n);get_ht(n);
        printf("%.10f\n",answer(1,n));
        clear();
    }
    return 0;
}