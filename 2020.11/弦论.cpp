#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
using namespace std;
char s[N];
int sa[N],rk[N],id[N];
int b[N];
void SA_(int n,int m)
{
	for(int i=0;i<=m;i++) b[i]=0;
	for(int i=1;i<=n;i++) b[rk[i]]++;
	for(int i=1;i<=m;i++) b[i]+=b[i-1];
	for(int i=n;i>=1;i--) sa[b[rk[id[i]]]--]=id[i];
}
void SA(int n)
{
	int m=124;
	for(int i=1;i<=n;i++) rk[i]=s[i]-'0'+1,id[i]=i;
	SA_(n,m);int t=0;
	for(int p=1;p<n;m=t,t=0,p<<=1)
	{
		for(int i=1;i<=p;i++) id[++t]=n-p+i;
		for(int i=1;i<=n;i++) if(sa[i]>p) id[++t]=sa[i]-p;
		SA_(n,m); swap(id,rk); rk[sa[1]]=t=1;
		for(int i=2;i<=n;i++) rk[sa[i]]=(t+=id[sa[i-1]]!=id[sa[i]] || id[sa[i-1]+p]!=id[sa[i]+p]);
	}
}
int ht[N],sum[N];
int mn[22][N],_2[N];
void get_ht(int n)
{
    for(int i=1,p=0;i<=n;ht[rk[i]]=p,i++)
    if(rk[i]!=1) for(p=p-!!p;i+p<=n && sa[rk[i]-1]+p<=n && s[i+p]==s[sa[rk[i]-1]+p];p++);
    for(int i=1;i<=n;i++) mn[0][i]=ht[i];
    for(int k=1;k<=_2[n];k++)
        for(int i=1;i<=n-(1<<k)+1;i++)
            mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<(k-1))]);
}
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1),t,k;
    for(int i=2;i<=n;i++) _2[i]=_2[i>>1]+1;
    scanf("%d%d",&t,&k);
    SA(n);
    get_ht(n);
    if(t==0)
    {
        for(int i=1;i<=n;i++)
        if(n-sa[i]-ht[i]+1<k) k-=n-sa[i]-ht[i]+1;
        else
        {
            for(int j=0;j<ht[i]+k;j++) putchar(s[sa[i]+j]);
            puts("");
            return 0;
        }
        puts("-1");
        return 0;
    }
    else
    {
        if(k>1ll*n*(n+1)/2){puts("-1");return 0;}
        int tot=0;
        for(int i=1;i<=n;i++)
        {
            int l=ht[i]+1;
            for(;l<=ht[i+1];l++)
            {
                int u=i,v=ht[i+1];
                for(int p=_2[n-i+1];p>=0;p--)
                    if(mn[p][u+1]>=l) v=min(v,mn[p][u+1]),u+=1<<p;
                int d=u-i+1,cnt=v-l+1;
                if(k-tot-1<=1ll*cnt*d)
                {
                    l+=(k-tot-1)/d;
                    for(int j=0;j<l;j++) putchar(s[sa[i]+j]);
                    return 0;
                }
                tot+=d*cnt;
                l=v;
            }
            int len=n-sa[i]-l+2;
            if(tot+len>=k)
            {
                for(int j=0;j<k-tot+l-1;j++) putchar(s[sa[i]+j]);
                return 0;
            }
            tot+=len;
        }
        puts("-1");
    }
    return 0;
}