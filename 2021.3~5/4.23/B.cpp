#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
int ch[N][26],len[N],fa[N],cnt=1;
int insert(int las,int c)
{
    int p=las;
    if(ch[p][c])
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) return np;
        else
        {
            int nq=++cnt;
            memcpy(ch[nq],ch[np],sizeof(ch[np]));
            fa[nq]=fa[np];len[nq]=len[p]+1;
            fa[np]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
            return nq;
        }
    }
    int q=las=++cnt;
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
            memcpy(ch[nq],ch[np],sizeof(ch[np]));
            fa[nq]=fa[np];len[nq]=len[p]+1;
            fa[np]=fa[q]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
    return q;
}
char s[N];
int siz[N],id[N];
ll f[N];
vector<int>ed;
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s+1);
            int m=strlen(s+1),las=1;
            for(int j=1;j<=m;j++) siz[las=insert(las,s[j]-'a')]++;
        }
        for(int i=1;i<=cnt;i++) id[i]=i;
        sort(id+1,id+cnt+1,[&](int x,int y){return len[x]<len[y];});
        for(int i=cnt;i;i--)
        {
            int u=id[i];
            for(int c=0;c<26;c++) f[u]=max(f[u],f[ch[u][c]]+siz[ch[u][c]]);
            if(u==1) break;
            siz[fa[u]]+=siz[u];
            f[fa[u]]=max(f[fa[u]],f[u]+1ll*(len[u]-len[fa[u]])*siz[u]);
        }
        printf("%lld\n",f[1]);
        for(int i=1;i<=cnt;i++) fa[i]=len[i]=siz[i]=id[i]=f[i]=0,memset(ch[i],0,sizeof(ch[i]));
        cnt=1;
    }
    return 0;
}