#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int id[N],sa[N],sum[N],rk[N];
int n,m;
void sa_sort()
{
	for(int i=0;i<=m;i++) sum[i]=0;
	for(int i=1;i<=n;i++) sum[rk[i]]++;
	for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
	for(int i=n;i>=1;i--) sa[sum[rk[id[i]]]--]=id[i];
}
char str[N];
void SA()
{
	m=122;
	for(int i=1;i<=n;i++) rk[i]=str[i]-'0'+1,id[i]=i;
	sa_sort();
	int tot=0;
	for(int p=1;tot<n;m=tot,p<<=1)
	{
		tot=0;
		for(int i=1;i<=p;i++) id[++tot]=n-p+i;
        for(int i=1;i<=n;i++) if(sa[i]>p) id[++tot]=sa[i]-p;
        sa_sort();
		swap(id,rk);
        rk[sa[1]]=tot=1;
        for(int i=2;i<=n;i++)
        {
        	if(id[sa[i-1]]!=id[sa[i]] || id[sa[i-1]+p]!=id[sa[i]+p]) ++tot;
        	rk[sa[i]]=tot;
		}
	}
}
int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	SA();
	for(int i=1;i<=n;i++) printf("%d ",sa[i]);
	return 0;
}

