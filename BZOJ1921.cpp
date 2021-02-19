#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 100010
#define C 26
#define B 800
#define ll long long
using namespace std;
vector<int>g[N];
char S[N],T[N];
bool cut[N];
vector<int>rv;
struct SAM{
    char s[N];
    int ch[N*2][C],len[N*2],fa[N*2],las,tot;
    int pos[N],ed[N*2];
    SAM(){las=tot=1;}
    int insert(int c,int d)
    {
        int p=las,q=las=++tot;
        len[q]=len[p]+1;ed[q]=d;ri[q]=1;
        for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
        if(!p) fa[q]=1;
        else
        {
            int np=ch[p][c];
            if(len[np]==len[p]+1) fa[q]=np;
            else
            {
                int nq=++tot;len[nq]=len[p]+1;
                memcpy(ch[nq],ch[np],sizeof(ch[np]));
                fa[nq]=fa[np];ed[nq]=ed[np];
                fa[np]=fa[q]=nq;
                for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            }
        }
        return q;
    }
    int c[N],id[N],ri[N],nxt[N][C],sm[N];
    void init(char S[])
    {
        int n=strlen(S+1);
        for(int i=1;i<=n;i++)
        {
            s[i]=S[i];
            pos[i]=insert(s[i]-'a',i);
        }
        for(int i=1;i<=tot;i++) c[len[i]]++;
        for(int i=2;i<=tot;i++) c[i]+=c[i-1];
        for(int i=1;i<=tot;i++) id[c[len[i]]--]=i;
        for(int i=tot;i;i--)
        {
            int u=id[i];ri[fa[u]]+=ri[u];
            nxt[fa[u]][s[ed[u]-len[fa[u]]]-'a']=u;
        }
    }
    void push(int tu,int tp,int u,int d,int op)
    {
        if(len[u]==d) u=nxt[u][T[tu]-'a'];
        else if(s[ed[u]-d]!=T[tu]) return;
        if(!u) return;
        if(op) sm[u]++; else rv.push_back(u);
        for(int tv:g[tu]) if(tv!=tp && !cut[tv]) push(tv,tu,u,d+1,op);
    }
    void set(int tu,int tp,int u,int v)
    {
        for(int i=1;i<=tot;i++) sm[i]=0;
        push(tu,tp,u,v,1);
        for(int i=1;i<=tot;i++) sm[id[i]]+=sm[fa[id[i]]];
    }
}s1,s2;
int siz[N],mx[N],rt,all;
void dfs0(int u,int p)
{
    siz[u]=1;
    for(int v:g[u]) if(v!=p && !cut[v]) dfs0(v,u),siz[u]+=siz[v];
}
void dfs1(int u,int p)
{
    mx[u]=1;
    for(int v:g[u])
    if(v!=p && !cut[v]) dfs1(v,u),mx[u]=max(mx[u],siz[v]);
    mx[u]=max(mx[u],all-siz[u]);
    if(!rt || mx[u]<mx[rt]) rt=u;
}
void get_node(int u,int p,vector<int>&f)
{
    f.push_back(u);
    for(int v:g[u]) if(v!=p && !cut[v]) get_node(v,u,f);
}
ll solve1(int u,int p,int pu)
{
    pu=s1.ch[pu][T[u]-'a'];
    if(!pu) return 0;ll res=s1.ri[pu];
    for(int v:g[u]) if(v!=p && !cut[v]) res+=solve1(v,u,pu);
    return res;
}
int n,m;
ll solve2(int u,int p)
{
    if(p) s1.set(u,p,s1.ch[1][T[p]-'a'],1),s2.set(u,p,s2.ch[1][T[p]-'a'],1);
    else s1.set(u,0,1,0),s2.set(u,0,1,0);
    ll res=0;
    for(int i=1;i<=m;i++) res+=1ll*s1.sm[s1.pos[i]]*s2.sm[s2.pos[m-i+1]];
    return res;
}
ll ans;
void work(int u)
{
    rt=0;
    dfs0(u,0);all=siz[u];
    dfs1(u,0);u=rt;
    if(siz[u]<=B)
    {
        vector<int>v;
        get_node(u,0,v);
        for(int i=0;i<(int)v.size();i++) ans+=solve1(v[i],0,1);
        for(int i=0;i<(int)v.size();i++) cut[v[i]]=true;
        return;
    }
    cut[u]=true;
    ans+=solve2(u,0);
    for(int v:g[u])
    if(!cut[v])
    {
        if(siz[v]>B) ans-=solve2(v,u);
        else
        {
            rv.clear();
            s1.push(v,u,s1.ch[1][T[u]-'a'],1,0);
            for(int i=0;i<(int)rv.size();i++) ans-=solve1(v,0,rv[i]);
        }
        work(v);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        g[u].push_back(v),g[v].push_back(u);
    }
    scanf("%s%s",T+1,S+1);
    s1.init(S);reverse(S+1,S+m+1);s2.init(S);
    work(1);
    printf("%lld\n",ans);
    return 0;
}