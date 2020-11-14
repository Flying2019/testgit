#include<iostream>
#include<cstdio>
#include<cstring>
#define N 300010
#pragma GCC optimize(2,3)
#define ll long long
#define re register
using namespace std;
char str[N];
int v[N];
int sa[N],rk[N],h[N],s[N<<1],op[N<<1],pos[N<<1],c1[N],c[N];
#define L(x) sa[c[s[x]]--]=x
#define R(x) sa[c[s[x]]++]=x
inline void sa_sort(int *S,int n,int m,int *s,int *op,int tn)
{
    for(re int i=1;i<=n;i++) sa[i]=0;
    for(re int i=1;i<=m;i++) c1[i]=0;
    for(re int i=1;i<=n;i++) c1[s[i]]++;
    for(re int i=2;i<=m;i++) c1[i]+=c1[i-1];
    for(re int i=1;i<=m;i++) c[i]=c1[i];
    for(re int i=tn;i;i--) L(S[i]);
    for(re int i=1;i<=m+1;i++) c[i]=c1[i-1]+1;
    for(re int i=1;i<=n;i++)
    if(sa[i]>1 && op[sa[i]-1]) R(sa[i]-1);
    for(re int i=1;i<=m;i++) c[i]=c1[i];
    for(re int i=n;i;i--)
    if(sa[i]>1 && !op[sa[i]-1]) L(sa[i]-1);
}
void SA_IS(int n,int m,int *s,int *op,int *pos)
{
    int tot=0,cnt=0;int *S=s+n;
    op[n]=0;
    for(re int i=n-1;i;i--) op[i]=(s[i]!=s[i+1])?s[i]>s[i+1]:op[i+1];
    rk[1]=0;
    for(re int i=2;i<=n;i++)
    if(op[i-1]==1 && op[i]==0) pos[++tot]=i,rk[i]=tot;
    else rk[i]=0;
    sa_sort(pos,n,m,s,op,tot);
    int u=0,p=0;
    for(re int i=1;i<=n;i++)
    if(rk[sa[i]])
    {
        u=rk[sa[i]];
        if(cnt<=1 || pos[u+1]-pos[u]!=pos[p+1]-pos[p]) ++cnt;
        else
        {
            for(re int j=0;j<=pos[u+1]-pos[u];j++)
            if(s[pos[u]+j]!=s[pos[p]+j] || op[pos[u]+j]!=op[pos[p]+j]){++cnt;break;}
        }
        S[u]=cnt;
        p=u;
    }
    if(tot!=cnt) SA_IS(tot,cnt,S,op+n,pos+n);
    else for(re int i=1;i<=tot;i++) sa[S[i]]=i;
    for(re int i=1;i<=tot;i++) S[i]=pos[sa[i]];
    sa_sort(S,n,m,s,op,tot);
}
int ht[N];
void get_ht(int n)
{
	for(re int i=1;i<=n;i++) rk[sa[i]=sa[i+1]]=i;
	for(re int i=1,p=0;i<=n;ht[rk[i]]=p,i++)
	if(rk[i]!=1) for(p=p-!!p;sa[rk[i]-1]+p<=n && i+p<=n && s[i+p]==s[sa[rk[i]-1]+p];p++);
}
namespace IP
{
    char buf[1<<23],*p1=buf,*p2=buf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    inline int rd()
    {
        int x=0,f=1;char ch=getchar();
        while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
        while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
        return x*f;
    }
    inline void rd(char s[])
    {
        int x=0;char ch=getchar();
        while(!isalpha(ch)) ch=getchar();
        while(isalpha(ch)) s[++x]=ch,ch=getchar();
    }
}
namespace OP
{
    char obuf[(1<<21)+1],st[19],*oS=obuf,*oT=obuf+(1<<21);
    void Flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
    void Put(char x){*oS++=x;if(oS==oT)Flush();}
    void write(ll x){int top=0;if(!x)Put('0');if(x<0) Put('-'),x=-x;while(x)st[++top]=(x%10)+48,x/=10;while(top)Put(st[top--]);Put(' ');}
}
int st;
int sh[N],sc[N],sx[N],sn[N];
ll an[N],av[N];
#define upd() an[sh[st]]+=1ll*sc[st]*cnt,av[sh[st]]=max(av[sh[st]],max(1ll*sx[st]*mx,1ll*sn[st]*mn))
int main()
{
    int n=IP::rd();
    IP::rd(str);
    for(int i=1;i<=n;i++) s[i]=str[i]-'a'+2;
    s[++n]=1;
    SA_IS(n--,28,s,op,pos);
    get_ht(n);
    for(re int i=1;i<=n;i++) v[i]=IP::rd();
    for(re int i=0;i<=n;i++) av[i]=-2000000000000000000;
    for(re int i=2;i<=n;i++)
    {
        int cnt=1,mx=v[sa[i-1]],mn=v[sa[i-1]];
        for(;st && sh[st]>=ht[i];cnt+=sc[st],mx=max(mx,sx[st]),mn=min(mn,sn[st]),st--) upd();
        sh[++st]=ht[i],sx[st]=mx,sn[st]=mn,sc[st]=cnt;
    }
    int cnt=1,mx=v[sa[n]],mn=v[sa[n]];
    for(;st;cnt+=sc[st],mx=max(mx,sx[st]),mn=min(mn,sn[st]),st--) upd();
    for(int i=n-1;i;i--) an[i-1]+=an[i],av[i-1]=max(av[i-1],av[i]);
    for(int i=n-1;i>=0;i--) if(!an[i]) av[i]=0;
    for(int i=0;i<n;i++) OP::write(an[i]),OP::write(av[i]),OP::Put('\n');
    OP::Flush();
    return 0;
}