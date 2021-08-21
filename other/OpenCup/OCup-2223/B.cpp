#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int s[N];
int ch[N][2],len[N],las=1,cnt=1;
int fa[N];
void insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[p]=np;
        else
        {
            int nq=++cnt;
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            fa[nq]=fa[np];len[nq]=len[p]+1;
            fa[np]=fa[q]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
}
int nxt[N];
void kmp(int n)
{
    for(int i=1;i<=n;i++)
    {
    }
}
int main()
{
    int n;
    long long seed;
    scanf("%d%lld",&n,&seed);
    for(int i=1;i<=n;i++) seed=(seed*13331+23333)%1000000007,s[i]=seed&1;
    for(int i=1;i<=n;i++)
    return 0;
}