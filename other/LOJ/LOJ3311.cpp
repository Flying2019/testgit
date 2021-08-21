#include<iostream>
#include<cstdio>
#include<cstring>
#define N 400010
using namespace std;
int id[N],_2[N];
struct SA{
    int h[N],rk[N],id[N],sa[N],b[N];
    void sort(int n,int m)
    {
        for(int i=0;i<=m;i++) b[i]=0;
        for(int i=1;i<=n;i++) b[rk[i]]++;
        for(int i=1;i<=m;i++) b[i]+=b[i-1];
        for(int i=n;i;i--) sa[b[rk[id[i]]]--]=id[i];
    }
    void work(int n,char s[])
    {
        int m=26;
        for(int i=1;i<=n;i++) rk[i]=s[i]-'a'+1,id[i]=i;
        sort(n,m);int t=0;
        for(int p=1;p<n;m=t,t=0,p<<=1)
        {
            for(int i=1;i<=p;i++) id[++t]=n-p+i;
            for(int i=1;i<=n;i++) if(sa[i]>p) id[++t]=sa[i]-p;
            sort(n,m);swap(id,rk);
            rk[sa[1]]=t=1;
            for(int i=2;i<=n;i++)
            rk[sa[i]]=(t+=id[sa[i-1]]!=id[sa[i]] || id[sa[i-1]+p]!=id[sa[i]+p]);
        }
    }
    int f[21][N];
    void height(char s[],int n)
    {
        for(int i=1,p=0;i<=n;h[rk[i]]=p,i++)
        if(rk[i]!=i) for(p=p-!!p;sa[rk[i]-1]+p<=n && i+p<=n && s[sa[rk[i]-1]+p]==s[i+p];p++);
        for(int i=1;i<=n;i++) f[0][i]=h[i];
        for(int k=1;k<=_2[n];k++)
            for(int i=1;i+(1<<k)-1<=n;i++) f[k][i]=min(f[k-1][i],f[k-1][i+(1<<(k-1))]);
    }
    int qry(int l,int r)
    {
        l=rk[l];r=rk[r];
        int k=_2[r-l];
        return min(f[k][l],f[k][r-(1<<k)]);
    }
};
char s[N];
void init(int n=N-10)
{
    for(int i=1;i<=n;i++) _2[i]=_2[i>>1]+1;
}
int main()
{
    int n,m;
    scanf("%d%d%s",&n,&m,s+1);
    return 0;
}