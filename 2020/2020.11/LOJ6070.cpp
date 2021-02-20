#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define C 27
#define B 343
using namespace std;
int ch[N][C],nxt[N][C];
int pos[B][N],fi[B][N],ans[B][N];
int len[N],fail[N];
int fr,las,cnt;
int vis[N],tm;
void init()
{
    fail[0]=fail[1]=cnt=1;len[1]=-1;
    for(int i=0;i<C;i++) ch[0][i]=1;
}
char s[N];
void push_front(int l,int r)
{
    int c=s[l]-'a',u=fr;
    if(l+len[u]+1>r || s[l]!=s[l+len[u]+1]) u=ch[u][c];
    if(!nxt[u][c])
    {
        int v=++cnt;
        len[v]=len[u]+2,fail[v]=nxt[ch[u][c]][c];
        memcpy(ch[v],ch[fail[v]],sizeof(ch[v]));
        ch[v][s[l+len[fail[v]]]-'a']=fail[v];
        nxt[u][c]=v;
    }
    fr=u=nxt[u][c];
    if(len[u]==r-l+1) las=fr;
}
void push_back(int l,int r)
{
    int c=s[r]-'a',u=las;
    if(r-len[u]-1<l || s[r]!=s[r-len[u]-1]) u=ch[u][c];
    if(!nxt[u][c])
    {
        int v=++cnt;
        len[v]=len[u]+2,fail[v]=nxt[ch[u][c]][c];
        memcpy(ch[v],ch[fail[v]],sizeof(ch[v]));
        ch[v][s[r-len[fail[v]]]-'a']=fail[v];
        nxt[u][c]=v;
    }
    las=u=nxt[u][c];
    if(len[u]==r-l+1) fr=las;
}
int bl[N];
int main()
{
    int ty,n,q;
    scanf("%d%d%d%s",&ty,&n,&q,s+1);
    init();
    memset(fi,0x3f,sizeof(fi));
    for(int l=1;l<=n;l+=B)
    {
        fr=las=0;++tm;
        for(int r=l;r<=n;r++)
        {
            push_back(l,r);
            ans[tm][r]=ans[tm][r-1];
            bl[r]=tm,pos[tm][r]=fr;
            if(vis[las]!=tm) vis[las]=tm,ans[tm][r]++,fi[tm][las]=r;
        }
    }
    int res=0;
    while(q --> 0)
    {
        int l,r;
        scanf("%d%d",&l,&r);++tm;
        l^=res*ty,r^=res*ty;res=0;
        if(bl[l]==bl[r])
        {
            fr=las=0;
            for(int i=l;i<=r;i++){push_back(l,i);if(vis[las]!=tm) vis[las]=tm,++res;}
        }
        else
        {
            int fl=bl[l]+1;
            fr=pos[fl][r],res=ans[fl][r];
            for(int i=bl[l]*B;i>=l;i--)
            {
                push_front(i,r);
                if(vis[fr]!=tm) vis[fr]=tm,res+=fi[fl][fr]>r;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}