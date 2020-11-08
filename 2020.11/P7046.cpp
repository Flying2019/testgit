#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<set>
#define ll long long
#define N 1000010
#define D 25
using namespace std;
int nxt[N<<2],to[N<<2],head[N<<1],rcnt;
void add(int u,int v){nxt[++rcnt]=head[u];to[rcnt]=v;head[u]=rcnt;}
int las=1,scnt=1,fa[N<<1],f[N][D],ch[N][26],len[N<<1],acnt,k;
int insert(int c)
{
    int p=las,q=las=++scnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
        else
        {
            int nq=++scnt;
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            len[nq]=len[p]+1;
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
    return q;
}
int pos[N],nd[N];
vector<int>ad[N];
set<int>s[N];
bool cmp(int a,int b){return len[a]<len[b];}
int work()
{
    int l,r;
    scanf("%d%d",&l,&r);
    int u=pos[r];
    ++acnt;
    len[acnt]=r-l+1;
    for(int i=D-1;i>=0;i--)
        if(f[u][i] && len[f[u][i]]>=len[acnt]) u=f[u][i];
    if(s[u].count(r-l+1)) return 0;
    s[u].insert(r-l+1);
    ad[u].push_back(acnt);
    return acnt;
}
void build()
{
    for(int i=2;i<=scnt;i++)
    {
        int p=fa[i];sort(ad[i].begin(),ad[i].end(),cmp);
        for(int v:ad[i]) add(p,v),p=v;
        add(p,i);
    }
}
int son[N<<1],siz[N<<1],dep[N<<1],ldep[N<<1];
void dfs1(int u)
{
    siz[u]=1;
    ldep[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];dep[v]=dep[u]+1;
        fa[v]=u;
        dfs1(v);
        if(siz[v]>siz[son[u]]) son[u]=v;
        siz[u]+=siz[v];
    }
    ldep[u]=ldep[son[u]]+1;
}
int ar[N*20],par;
int* _new(int k){par+=k;return ar+(par-k);}
int* b[N<<1];int g[N<<1],d[N<<1];
int top[N<<1],pp[N<<1];
void dfs2(int u,int topp)
{
    top[u]=topp;
    if(son[u]) dfs2(son[u],topp);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v!=son[u]) dfs2(v,v);
    }
    if(u==topp) b[u]=_new(ldep[u]+1),pp[u]=u;
}
ll ans;int res;
void upd(int u)
{
    if(dep[u]<dep[pp[top[u]]]) return;
    b[top[u]][dep[u]-dep[top[u]]+1]--;g[top[u]]++;
    u=top[u];
    while(pp[u])
    {
        if(g[u]+b[u][dep[pp[u]]-dep[u]]>k)
        {
            ans+=len[pp[u]]-len[fa[pp[u]]];
            res=max(res,len[pp[u]]);
            g[u]+=b[u][dep[pp[u]]-dep[u]];
            pp[u]=son[pp[u]];
        }
        else break;
    }
}
void ins(int u){for(;u;u=fa[top[u]]) upd(u);}
char str[N];
int main()
{
    int n,m;
    scanf("%d%d%d%s",&n,&m,&k,str+1);
    for(int i=1;i<=n;i++) pos[i]=insert(str[i]-'a');
    for(int i=1;i<=scnt;i++) f[i][0]=fa[i];
    for(int j=1;j<D;j++)
        for(int i=1;i<=scnt;i++) f[i][j]=f[f[i][j-1]][j-1];
    acnt=scnt;
    for(int i=1;i<=m;i++) nd[i]=work();
    for(int i=1;i<=scnt;i++) s[i].clear();
    build();
    len[0]=-1;
    dfs1(1);dfs2(1,1);
    for(int i=1;i<=m;i++)
    {
        if(nd[i]) ins(nd[i]);
        printf("%lld %d\n",ans,res);
    }
    return 0;
}