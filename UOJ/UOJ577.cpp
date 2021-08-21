#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#define MP make_pair
#define N 1000010
#define ull unsigned long long
using namespace std;
map<char,int>id({MP('A',0),MP('C',1),MP('T',2),MP('G',3)});
struct SAM{
    int ch[N][4],len[N],fa[N],pos[N];
    bool ed[N];
    int las=1,cnt=1;
    void insert(int c,int d)
    {
        int p=las,q=las=++cnt;
        len[q]=len[p]+1;pos[q]=d;ed[q]=true;
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
                pos[nq]=pos[np],fa[nq]=fa[np];
                fa[np]=fa[q]=nq;
                for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            }
        }
    }
    vector<int>g[N];
    void init(){for(int i=2;i<=cnt;i++) g[fa[i]].push_back(i);}
}sa;
char s[N];
ull lf[N],rf[N],f[N];
int b[N],p[N],cnt[N],siz[N],nxt[N],dis[N],n;
ull psum[N],sum[N];
void dfss(int u)
{
    siz[u]+=sa.ed[u],psum[u]=sa.ed[u]*rf[sa.pos[u]];
    for(int v:sa.g[u]) dfss(v),siz[u]+=siz[v],psum[u]+=psum[v];
    sum[u]=psum[u]*siz[u];
}
bool rem[N];
void dfsp(int u,int l,ull sm)
{
    if(rem[u]) f[n-l+1]=sm;
    for(int i=0;i<4;i++)
    {
        int v=sa.ch[u][i];
        if(v) dfsp(nxt[v],l+dis[v],sm+sum[v]);
    }
}
void compr()
{
    for(int i=1;i<=sa.cnt;i++) b[sa.len[i]]++;
    for(int i=1;i<=n;i++) b[i]+=b[i-1];
    for(int i=sa.cnt;i;i--) p[b[sa.len[i]]--]=i;
    for(int p=sa.las;p;p=sa.fa[p]) rem[p]=true;
    for(int i=sa.cnt;i;i--)
    {
        int u=p[i],c=0,v=0;
        for(int j=0;j<4;j++)
        if(sa.ch[u][j]) c++,v=sa.ch[u][j];
        if(c==1 && !rem[u]) nxt[u]=nxt[v],sum[u]+=sum[v],dis[u]=dis[v]+1;
        else nxt[u]=u,dis[u]=1;
    }
}
int main()
{
    int q;
    scanf("%d%d%s",&n,&q,s+1);
    for(int i=1;i<=n;i++) scanf("%llu",&lf[i]);
    for(int i=1;i<=n;i++) scanf("%llu",&rf[i]);
    for(int i=1;i<=n;i++) sa.insert(id[s[i]],i);
    sa.init();
    dfss(1);compr();
    dfsp(1,0,0);
    ull ans=0;
    for(int i=1;i<=n;i++) ans+=lf[i]*f[i];
    printf("%llu\n",ans);
    while(q --> 0)
    {
        int u;ull v;
        scanf("%d%llu",&u,&v);
        ans+=(v-lf[u])*f[u];
        lf[u]=v;
        printf("%llu\n",ans);
    }
    return 0;
}