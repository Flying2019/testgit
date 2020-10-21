#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
using namespace std;
char str[N];
int sa[N],rk[N],h[N],s[N<<1],op[N<<1],pos[N<<1],c1[N],c[N];
#define L(x) sa[c[s[x]]--]=x
#define R(x) sa[c[s[x]]++]=x
void sa_sort(int *S,int n,int m,int *s,int *op,int tn)
{
    for(int i=1;i<=n;i++) sa[i]=0;
    for(int i=1;i<=m;i++) c1[i]=0;
    for(int i=1;i<=n;i++) c1[s[i]]++;
    for(int i=2;i<=m;i++) c1[i]+=c1[i-1];
    for(int i=1;i<=m;i++) c[i]=c1[i];
    for(int i=tn;i;i--) L(S[i]);
    for(int i=1;i<=m+1;i++) c[i]=c1[i-1]+1;
    for(int i=1;i<=n;i++)
    if(sa[i]>1 && op[sa[i]-1]) R(sa[i]-1);
    for(int i=1;i<=m;i++) c[i]=c1[i];
    for(int i=n;i;i--)
    if(sa[i]>1 && !op[sa[i]-1]) L(sa[i]-1);
}
void SA_IS(int n,int m,int *s,int *op,int *pos)
{
    int tot=0,cnt=0;int *S=s+n,*Op=op+n,*Pos=pos+n;
    op[n]=0;
    for(int i=n-1;i;i--) op[i]=(s[i]!=s[i+1])?s[i]>s[i+1]:op[i+1];
    rk[1]=0;
    for(int i=2;i<=n;i++)
    if(op[i-1]==1 && op[i]==0) pos[++tot]=i,rk[i]=tot;
    else rk[i]=0;
    sa_sort(pos,n,m,s,op,tot);
    int u=0,p=0;
    for(int i=1;i<=n;i++)
    if(rk[sa[i]])
    {
        u=rk[sa[i]];
        if(cnt<=1 || pos[u+1]-pos[u]!=pos[p+1]-pos[p]) ++cnt;
        else
        {
            for(int j=0;j<=pos[u+1]-pos[u];j++)
            if(s[pos[u]+j]!=s[pos[p]+j] || op[pos[u]+j]!=op[pos[p]+j]){++cnt;break;}
        }
        S[u]=cnt;
        p=u;
    }
    if(tot!=cnt) SA_IS(tot,cnt,S,Op,Pos);
    else for(int i=1;i<=tot;i++) sa[S[i]]=i;
    for(int i=1;i<=tot;i++) S[i]=pos[sa[i]];
    sa_sort(S,n,m,s,op,tot);
}
int ht[N];
void get_ht(int n)
{
	for(int i=1;i<=n;i++) rk[sa[i]=sa[i+1]]=i;
	for(int i=1,p=0;i<=n;ht[rk[i]]=p,i++)
	if(rk[i]!=1) for(p=p-!!p;sa[rk[i]-1]+p<=n && i+p<=n && s[i+p]==s[sa[rk[i]-1]+p];p++);
}
int main()
{
    scanf("%s",str+1);
    int n=strlen(str+1);
    for(int i=1;i<=n;i++) s[i]=str[i]-'a'+2;
    s[++n]=1;
    SA_IS(n--,28,s,op,pos);
    get_ht(n);
    for(int i=1;i<=n;i++) printf("%d ",sa[i]);puts("");
    for(int i=2;i<=n;i++) printf("%d ",ht[i]);
    return 0;
}