#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 600010
#define db double
#define alp 0.72
#define MAXD 1e16
#define inf 1e17
#define mod 1019260817
using namespace std;
char str[N];
db v[N];
int ch[N][2],siz[N];
int swp[N],stot,rt;
void upd(int u){siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;}
void dfs(int u)
{
    if(!u) return;
    dfs(ch[u][0]),swp[++stot]=u;dfs(ch[u][1]);
    ch[u][0]=ch[u][1]=0;
}
void build(int &u,int l,int r,db lf=0,db rf=MAXD)
{
    if(l>r) return;
    int mid=(l+r)>>1;db mf=(lf+rf)/2;
    u=swp[mid];
    v[u]=mf;
    build(ch[u][0],l,mid-1,lf,mf),build(ch[u][1],mid+1,r,mf,rf);
    upd(u);
}
void reb(int &u,db lf,db rf)
{
    if(max(siz[ch[u][0]],siz[ch[u][1]])<siz[u]*alp) return;
    stot=0;dfs(u);
    build(u,1,stot,lf,rf);
}
int cmp(int x,int y){return str[x]==str[y]?v[x-1]<v[y-1]:str[x]<str[y];}
void insert(int &u,int k,db lf=0,db rf=MAXD)
{
    if(!u){siz[u=k]=1;v[u]=(lf+rf)/2;ch[u][0]=ch[u][1]=0;return;}
    if(cmp(k,u)) insert(ch[u][0],k,lf,v[u]);
    else insert(ch[u][1],k,v[u],rf);
    upd(u),reb(u,lf,rf);
}
int hs[N],bs[N];
int get(int l,int r){return (hs[r]-1ll*hs[l-1]*bs[r-l+1]%mod+mod)%mod;}
bool cmps(int x,int y,bool op)
{
    if(x<=y && hs[x]==get(y-x+1,y)) return !op;
    return v[x]<v[y];
}
int answer(int u,int p,bool op)
{
    if(!u) return 0;
    if(cmps(p,u,op)) return answer(ch[u][0],p,op);
    else return answer(ch[u][1],p,op)+siz[ch[u][0]]+1;
}
char opt[7],s[5];
const int B=233;
int main()
{
    int n,las=0;
    scanf("%d",&n);
    bs[0]=1;
    for(int i=1;i<=n;i++) bs[i]=1ll*bs[i-1]*B%mod;
    int m=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",opt);
        if(opt[0]=='a')
        {
            scanf("%s",s+1);
            s[1]=(s[1]-'a'+las)%26+'a';
            str[++m]=s[1];hs[m]=(1ll*hs[m-1]*B+s[1]-'a'+1)%mod;
            insert(rt,m);
        }
        else
        {
            int k;
            scanf("%d",&k);
            k=(k-1+las)%m+1;
            printf("%d\n",las=answer(rt,k,1)-answer(rt,k,0));
        }
    }
    return 0;
}