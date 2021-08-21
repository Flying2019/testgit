#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 400010
#define C 26
#define ll long long
using namespace std;
int ch[N][C],fa[N],len[N],siz[N],las=1,cnt=1;
void insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;siz[q]++;
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
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
}
char s[N];
int id[N];ll f[N];
int main()
{
    int n;
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++) insert(s[i]-'a');
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
    return 0;
}