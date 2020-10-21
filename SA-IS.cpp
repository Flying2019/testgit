#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;
char str[N];
int sa[N],rk[N],h[N],s[N<<1],op[N<<1],pos[N<<1],c1[N],c2[N];
void sa_sort(int *S,int n,int m,int *s,int *op,int tn)
{
    memset(sa+1,0,sizeof(int)*n);
    memset(c1+1,0,sizeof(int)*m);
    for(int i=1;i<=n;i++) c1[s[i]]++;
    for(int i=2;i<=n;i++) c1[i]+=c1[i-1];
    for(int i=1;i<=n;i++) c2[i]=c1[i];
    for(int i=tn;i;i--) sa[c2[S[i]]--]=S[i];
    for(int i=1;i<=n;i++) c2[i]=c1[i-1]+1;
    for(int i=1;i<=n;i++)
    if(sa[i]>1 && op[sa[i]-1])
        sa[c2[sa[i]-1]++]=sa[i]-1;
    for(int i=1;i<=n;i++) c2[i]=c1[i];
    for(int i=n;i;i--)
    if(sa[i]>1 && !op[sa[i]-1])
        sa[c2[sa[i]-1]--]=sa[i]-1;
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
            if(s[u+j]!=s[p+j] || op[u+j]!=op[p+j]){++cnt;break;}
        }
        S[u]=cnt;
        p=u;
    }
    if(tot!=cnt) SA_IS(tot,cnt,S,Op,Pos);
    else for(int i=1;i<=tot;i++) sa[S[i]]=i;
    for(int i=1;i<=tot;i++) S[i]=pos[sa[i]];
    sa_sort(S,n,m,s,op,tot);
}
int tmp[310];
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
    SA_IS(n--,27,s,op,pos);
    get_ht(n);
    for(int i=1;i<=n;i++) printf("%d ",sa[i]+1);puts("");
    for(int i=2;i<=n;i++) printf("%d ",ht[i]);
    return 0;
}
/*
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
#include<numeric>
using std::partial_sum;
using std::transform;
using std::for_each;
namespace IO
{
    char obuf[(1<<21)+1],st[11],*oS=obuf,*oT=obuf+(1<<21);
    void Flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
    void Put(char x){*oS++=x;if(oS==oT)Flush();}
    void write(int x){int top=0;if(!x)Put('0');while(x)st[++top]=(x%10)+48,x/=10;while(top)Put(st[top--]);Put(' ');}
}using namespace IO;
const int N=1000007;
char str[N+10];int sa[N],rank[N],h[N],s[N<<1],t[N<<1],pos[N<<1],r[N>>1],c[N>>1];
#define is(x,a) sa[r[s[x]]a]=x
#define IS(S)\
    memset(sa+1,0,n<<2),memset(c+1,0,m<<2),for_each(s+1,s+n+1,[](int x){++c[x];}),partial_sum(c+1,c+m+1,c+1),memcpy(r+1,c+1,m<<2);\
    for(int i=N;i;--i) is(S[i],--);\
    transform(c,c+m,r+1,[](int x){return x+1;});\
    for(int i=1;i<=n;++i) if(sa[i]>1&&t[sa[i]-1]) is(sa[i]-1,++);\
    memcpy(r+1,c+1,m<<2);\
    for(int i=n;i;--i) if(sa[i]>1&&!t[sa[i]-1]) is(sa[i]-1,--);
void SAIS(int n,int m,int*s,int*t,int*pos)
{
    int N=0,M=rank[1]=0,*S=s+n;
    t[n]=0;
    for(int i=n-1;i;--i) t[i]=s[i]^s[i+1]? s[i]>s[i+1]:t[i+1];
    for(int i=2;i<=n;++i) rank[i]=t[i-1]&&!t[i]? pos[++N]=i,N:0;
    IS(pos);
    for(int i=1,x,y=0;i<=n;++i)
	if((x=rank[sa[i]]))
	{
	    if(M<=1||pos[x+1]-pos[x]!=pos[y+1]-pos[y]) ++M;
	    else for(int a=pos[x],b=pos[y];a<=pos[x+1];++a,++b) if((s[a]<<1|t[a])^(s[b]<<1|t[b])) {++M;break;}
	    S[y=x]=M;
	}
    if(M^N) SAIS(N,M,S,t+n,pos+n); else for(int i=1;i<=N;++i) sa[S[i]]=i;
    for(int i=1;i<=N;++i) S[i]=pos[sa[i]];
    IS(S);
}
int main()
{
    int n;
    fread(str+1,1,1000000,stdin),n=strlen(str+1);
    while(!isalpha(str[n])) --n;
    transform(str+1,str+n+1,s+1,[](char c){return c-'a'+2;}),s[++n]=1,SAIS(n--,27,s,t,pos);
    for(int i=1;i<=n;++i) rank[sa[i]=sa[i+1]]=i;
    for(int i=1,j,l=0;i<=n;h[rank[i++]]=l) for(j=sa[~-rank[i]],l-=l>0;i+l<=n&&j+l<=n&&s[i+l]==s[j+l];++l);
    for_each(sa+1,sa+n+1,[](int x){write(x);}),Put('\n'),for_each(h+2,h+n+1,[](int x){write(x);}),Flush();
}
*/