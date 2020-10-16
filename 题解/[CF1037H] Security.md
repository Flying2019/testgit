### [链接](https://www.luogu.com.cn/problem/CF1037H)
首先看到子串，考虑用SAM。再看到严格大于，可以发现SAM本质是一个字符转移，每一条路径对应一个字符串，所以符合贪心的原则。

假如 $l=1,r=n$，我们可以直接建出SAM，然后每次跑转移时我们跑比 $s_i$ 大的尽可能小的转移边。

特别的，由于题目要求严格大于，所以我们跑转移边同时记录严格大于的转移边。

再考虑一般情况。按照套路，我们把每个节点的endpos集合用线段树合并处理出来。

显然，假如一个节点的endpos集合中存在一个位置使该串完全位于 $[l,r]$ 中，那么该字符串在 $[l,r]$ 中出现过。显然又有其祖先的endpos包含该点的endpos。所以该转移在子串 $[l,r]$ 中存在。

显然，我们只需要对每次转移判断是否存在于 $[l,r]$ 即可。复杂度 $O(n\log n)$。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define N 200010
int fa[N],ch[N][26],len[N],cnt=1,las=1;
int ls[N*40],rs[N*40],ntot,n;
int nxt[N<<1],to[N<<1],head[N],rcnt;
int root[N];
void insert(int &u,int l,int r,int p)
{
    if(!u) u=++ntot;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls[u],l,mid,p);
    else insert(rs[u],mid+1,r,p);
}
void insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    insert(root[q],1,n,len[q]);
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
        else
        {
            int nq=++cnt;
            memcpy(ch[nq],ch[np],sizeof(ch[nq]));
            fa[nq]=fa[np];
            fa[np]=fa[q]=nq;
            len[nq]=len[p]+1;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
}
int answer(int u,int l,int r,int L,int R)
{
    if(!u || L>R || l>R || L>r) return false;
    if(L<=l && r<=R) return true;
    int mid=(l+r)>>1;
    return answer(ls[u],l,mid,L,R) || answer(rs[u],mid+1,r,L,R);
}
int merge(int x,int y)
{
    if(!x || !y) return x+y;
    int u=++ntot;
    ls[u]=merge(ls[x],ls[y]);
    rs[u]=merge(rs[x],rs[y]);
    return u;
}
void add(int u,int v)
{
    nxt[++rcnt]=head[u];
    to[rcnt]=v;
    head[u]=rcnt;
}
void dfs(int u)
{
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        dfs(v);
        root[u]=merge(root[u],root[v]);
    }
}
char s[N];
int zy[N];
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++) insert(s[i]-'a');
    for(int i=2;i<=cnt;i++) add(fa[i],i);
    dfs(1);
    int m;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        scanf("%s",s+1);
        int len=strlen(s+1),u=1,p;
        for(p=1;;p++)
        {
            zy[p]=-1;
            for(int c=p>len?0:s[p]-'a'+1;c<26;c++)
            {
                int v=ch[u][c];
                if(v && answer(root[v],1,n,l+p-1,r)){zy[p]=c;break;}
            }
            int v=p>len?0:ch[u][s[p]-'a'];
			if(!v || p==n+1 || !answer(root[v],1,n,l+p-1,r)) break;
			u=v;
        }
        for(;p && zy[p]==-1;p--);
		if(!p) {puts("-1");continue;}
		else
        {
			for(int j=1;j<p;j++) putchar(s[j]);
			putchar('a'+zy[p]);puts("");
		}
    }
    return 0;
}
```
