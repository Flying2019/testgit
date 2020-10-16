### [����](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2991)
���ȿ��Է��� $(x\oplus X)\oplus X=x$����Ҫ�� $x$ ���ܺ� $x\oplus X$ ͬʱ���뼯�ϡ����� $Xor$ �����²������������ơ�

������ĿҪ�� $2^{n+1}$ Ԫ������һ�루$2\oplus n$��ѡ�С����ݸ���ԭ������ÿ�� $(x,x\oplus X)$ �����ҽ���һ����ѡ�С���Ӧ��[2-sat](https://www.luogu.com.cn/problem/P4782)ģ�͡�

���Է��֣����� $And,\ Or$ �����ƣ�������һ���Ӽ�/�����������ƶ���Ϊ $O(3^n)$����2-sat�� $O(n+m)$��ֱ��������2-sat���Ӷ� $O(2^n+3^n)$�����Խ��ܡ�

���Զ���ÿ�� $Ans,\ Or$ ���ƣ�ֱ������ $x\rightarrow y\oplus X,y\rightarrow x\oplus X$������2-satֱ���װ��Ӽ��ɡ�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N (1<<15)+10
#define M 1<<26
using namespace std;
int dfn[N],low[N],in[N];
int stack[N],top,cnt;
int nxt[M],to[M],head[N];
int s[N],num,n;
void add(int u,int v)
{
	++u,++v;
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
void tarjan(int now)
{
	dfn[now]=low[now]=++cnt;
	stack[top++]=now;
	in[now]=true;
	for(int i=head[now];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[now]=min(low[v],low[now]);
		}
		else if(in[v])low[now]=min(dfn[v],low[now]);
	}
	if(low[now]==dfn[now])
	{
		int u;
		++num;
		do
		{
			u=stack[--top];
			in[u]=false;
			s[u]=num;
		}
		while(u!=now);
	}
}
int wx,wa,wo;
bool can(void)
{
	for(int i=1;i<=n;i++)
	if(!dfn[i]) tarjan(i);
	for(int i=0;i<n;i++) s[i]=s[i+1];
	for(int i=0;i<n;i++) if(s[i]==s[i^wx]) return false;
	return true;
}
int ans[N],tot;
int main()
{
	scanf("%d%d%d%d",&n,&wx,&wa,&wo);
	if(!wx){puts("No");return 0;}
	int m=1<<(n+1);
	for(int s=0;s<m;s++)
	{
		if((s&wa)==wa)
		{
			int s0=(m-1)&(~s);
			for(int t=s0;;t=(t-1)&s0)
			{
				int u=wa|t;
				add(s,u^wx);
				add(u,s^wx);
				if(!t) break;
			}
		}
		if((s|wo)==wo)
		{
			for(int t=s;;t=(t-1)&s)
			{
				int u=(wo^s)|t;
				add(s,u^wx);
				add(u,s^wx);
				if(!t) break;
			}
		}
	}
	n=m;
	if(!can()) printf("No");
	else
	{
		puts("Yes");
		for(int i=0;i<m;i++)
		if(s[i]<s[i^wx]) ans[++tot]=i;
		for(int i=1;i<=tot;i++) printf("%d%s",ans[i],i==tot?"\n":" ");
	}
	return 0;
}
```
