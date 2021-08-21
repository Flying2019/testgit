#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
#define C 26
using namespace std;
typedef char T;
char s[N];int n;
int ch[N][C],nxt[N]={0,1},fa[N],len[N];
const T *pos[N];
int tot=1,rm,ac=1,acs=1;
void make(int u,int v){fa[u]=v;ch[v][pos[u][len[v]+1]]=u;}
void push_back(const T &c)
{
    int pre=0;
    ++rm;
    while(rm)
    {
        if(rm<=len[ac])
        {
            if(pos[ac][rm]==c) break;
            int nq=++tot;
            len[nq]=rm-1;
            pos[nq]=pos[ac];
            nxt[nq]=1;
            make(nq,fa[ac]),make(ac,nq);
            ac=nq;
        }
        else if(ch[ac][c]) break;
        int u=++tot;
        pos[u]=&c-rm;
        len[u]=n-((T *)pos[u]-s)-1;
        make(u,ac);
        --rm;
        pre=ac;acs=u;
        if(ac!=1)
        {
            ac=nxt[fa[ac]];
            for(const T *ps=&c-rm;len[ac]<rm-1;ac=ch[ac][ps[len[ac]+1]]);
        }
    }
    if(pre>1) nxt[pre]=ac;
    if(rm>len[ac]) ac=ch[ac][c];
}
int main()
{
    int n;
    scanf("%d",&n);
    return 0;
}