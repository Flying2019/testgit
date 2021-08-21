#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200010
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define M 4
using namespace std;
struct matr{
    ll a[M][M];
    ll* operator [](int x){return a[x];}
    matr(ll x=0){memset(a,0,sizeof(a));for(int _=0;_<M;_++) a[_][_]=x;}
}o;
matr operator *(matr &a,matr &b)
{
    matr c;memset(&c,0x3f,sizeof(c));
    for(int k=0;k<4;k++)
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++) c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
    return c;
}
matr ksm(matr o,ll k)
{
    matr c(1);
    for(;k;k>>=1,o=o*o)
    if(k&1) c=c*o;
    return c;
}
int ch[N][M],len[N],fa[N];
int las=1,cnt=1;
int insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
        else
        {
            int nq=++cnt;
            len[nq]=len[p]+1;
            memcpy(ch[nq],ch[np],sizeof(ch[np]));
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
    return q;
}
bool vis[N];
int g[N][4],n;
void dfs(int u)
{
    if(vis[u]) return;
    vis[u]=true;
    for(int i=0;i<4;i++)
    if(ch[u][i])
    {
        dfs(ch[u][i]);
        for(int j=0;j<4;j++) g[u][j]=min(g[u][j],g[ch[u][i]][j]+1);
    }
    else g[u][i]=1;
}
char s[N];
void init()
{
    for(int i=1;i<=n;i++) insert(s[i]-'A');
    dfs(1);
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++) o[i][j]=g[ch[1][i]][j];
}
bool check(ll x,ll k)
{
    matr c=ksm(o,x);
    ll mn=inf;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++) mn=min(mn,c[i][j]);
    return mn<=k;
}
int main()
{
    ll k;
    memset(g,0x3f,sizeof(g));
    scanf("%lld%s",&k,s+1);
    n=strlen(s+1);
    init();
    ll l=1,r=k,res=0;
    while(l<=r)
    {
        ll mid=(l+r)>>1;
        if(check(mid,k)) l=mid+1,res=mid;
        else r=mid-1;
    }
    if(check(res,k-1)) res++;
    printf("%lld\n",res);
    return 0;
}