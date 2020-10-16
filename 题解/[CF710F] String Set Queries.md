### [����](http://codeforces.com/problemset/problem/710/F)
�ַ������⡣

�����മƥ�䵥���������ʵĻ������Ӵ����Ǵ���ʾ���AC�Զ����ˡ�

�������ǿ��Է��֣����ڡ����ִ������ǿɲ�ֵģ��������ǿ��Զ���ɾ�����ַ������¿�һ��AC�Զ�������ô���Ĵ𰸾��������Զ��������

��������ˣ���Ȼ�����ܡ�������ܱ�����2400���������ɵģ��Ǿ���**ǿ������**�������岽���ⷨ����

���Է�������AC�Զ�����failָ���ǲ�֧�ּ���һ�����ģ���Ϊ������ᵼ�� $O(n)$ �ĸ��Ӷȡ�

��ô�������ô����

�����������������ֱ�����

1. ÿ����һ���ַ��������½���AC�Զ�����Ԥ���� $O(n|s|)$����ѯ $O(|s|)$��
2. ��������ѯ�ʣ�Ԥ���� $O(|s|)$����ѯ $O(n|s|)$��

��ô������Ȼ������һ�����ŷ��ε��������������ַ���ÿ $\sqrt n$ ��һ�飬���ڽ�AC�Զ�����ʣ�౩����

��Ȼ����������������һ������������������Ƿ��ֽ��飬�����ʣ�ಿ�ֱ������ӶȻ�ܸߣ�����齨С�˺��˷ѣ���Ϊ��������ǲ��������κθĶ������Ҳ�ѯ**ʱ�临�Ӷ���鳤�޹�**��

��ô���ǾͿ��Ե������С��������˵�����ǲ���һ����ʱ���¿�һ���飬���СΪ1������ $\texttt{[8 2 1 | 1]}$��

Ȼ�����ǲ������Һϲ���ͬ�Ŀ顣�����ϲ��ɵĿ�Ϊ $\texttt{[8 4]}$��

�����������Ӷ��Ƕ��٣�һ������ᱻ�ϲ� $O(\log n)$ �Σ�һ�β�ѯ����ѯ $O(\log n)$ ���飬������ʱ�临�Ӷ� $O(|s|\log n)$��
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
