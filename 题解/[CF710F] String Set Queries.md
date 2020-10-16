### [链接](http://codeforces.com/problemset/problem/710/F)
字符串好题。

看到多串匹配单串，而且问的还不是子串，那大概率就是AC自动机了。

首先我们可以发现，由于“出现次数”是可差分的，所以我们可以对于删掉的字符串重新开一个AC自动机。那么最后的答案就是两个自动机相减。

这就做完了？当然不可能。这道题能被评到2400还是有理由的，那就是**强制在线**（又是五步出题法）。

可以发现我们AC自动机的fail指针是不支持加入一个串的，因为这样最坏会导致 $O(n)$ 的复杂度。

那么这题该怎么处理？

考虑我们现在有两种暴力：

1. 每加入一个字符串，重新建立AC自动机，预处理 $O(n|s|)$，查询 $O(|s|)$。
2. 暴力处理询问，预处理 $O(|s|)$，查询 $O(n|s|)$。

那么这样显然就有了一个根号分治的做法。把所有字符串每 $\sqrt n$ 分一块，块内建AC自动机，剩余暴力。

当然，对于这题我们有一个更优秀的做法。我们发现建块，块大了剩余部分暴力复杂度会很高，如果块建小了很浪费，因为这个块我们不会再做任何改动，而且查询**时间复杂度与块长无关**。

那么我们就可以调整块大小。具体来说，我们插入一个串时先新开一个块，块大小为1。比如 $\texttt{[8 2 1 | 1]}$。

然后我们不断向右合并相同的块。即最后合并成的块为 $\texttt{[8 4]}$。

考虑这样复杂度是多少？一个块会多会被合并 $O(\log n)$ 次，一次查询最多查询 $O(\log n)$ 个块，所以总时间复杂度 $O(|s|\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 300010
using namespace std;
int ch[N*4][26],nxt[N*4][26],val[N*4],ed[N*4],fail[N*4],tot;
int ton[N*4],tt;
int new_node(){if(tt) return ton[tt--];return ++tot;}
void erase(int &u){memset(ch[u],0,sizeof(ch[u]));memset(nxt[u],0,sizeof(nxt[u]));fail[u]=ed[u]=val[u]=0;ton[++tt]=u;u=0;}
int rt[N];
void insert(int &rt,char s[],int l)
{
	if(!rt) rt=new_node();
	int u=rt;
	for(int i=1;i<=l;i++)
	{
		int c=s[i]-'a';
		if(!ch[u][c]) ch[u][c]=new_node();
		u=ch[u][c];
	}
	ed[u]++;
}
queue<int>q;
void make_fail(int p)
{
	for(int i=0;i<26;i++)
	if(ch[p][i]) nxt[p][i]=ch[p][i],fail[ch[p][i]]=p,q.push(ch[p][i]);
	else nxt[p][i]=p;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<26;i++)
		if(ch[u][i]) fail[nxt[u][i]=ch[u][i]]=nxt[fail[u]][i],q.push(ch[u][i]);
		else nxt[u][i]=nxt[fail[u]][i];
		val[u]=val[fail[u]]+ed[u];
	}
}
void merge(int &x,int &y)
{
	if(!x || !y){x=x+y;y=0;return;}
	for(int i=0;i<26;i++) merge(ch[x][i],ch[y][i]);
	ed[x]+=ed[y];erase(y);
}
struct ACM{
	int rts[N],siz[N],tt;
	void insert(char s[],int l)
	{
		siz[++tt]=1;
		::insert(rts[tt],s,l);
		for(;tt>1 && siz[tt]==siz[tt-1];siz[tt--]=0){merge(rts[tt-1],rts[tt]);siz[tt-1]+=siz[tt];}
		make_fail(rts[tt]);
	}
	long long answer(char s[],int l)
	{
		long long ans=0;
		for(int i=1;i<=tt;i++)
		{
			int u=rts[i];
			for(int j=1;j<=l;j++)
			u=nxt[u][s[j]-'a'],ans+=val[u];
		}
		return ans;
	}
}v,dv;
char str[N];
int len;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int opt;
		scanf("%d%s",&opt,str+1);
		len=strlen(str+1);
		if(opt==1) v.insert(str,len);
		else if(opt==2) dv.insert(str,len);
		else printf("%lld\n",v.answer(str,len)-dv.answer(str,len));
		fflush(stdout);
	}
	return 0;
}
```
