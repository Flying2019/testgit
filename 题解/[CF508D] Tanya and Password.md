### [����](http://codeforces.com/problemset/problem/508/D)
ŷ����·��

���ǽ�һ������Ϊ2���ַ�������һ���㣬��ô��Ŀ�������Ǹ��� $n$ ������ߣ���ŷ����·��

���� $\texttt{abb}$ �Ϳ��Կ��� $\texttt{ab}\ \rightarrow\ \texttt{bb}$ ��һ���ߡ�

����ͬ�ĵ����ܹ�ֻ�в���10000��������ֱ�Ӵ���

������ŷ����·����һ�ֺܼ��������������ȱ�����һ��·����ע����������õ�����ʽǰ���ǣ�һ��Ҫ�� $\&$ �ţ�
```cpp
void dfs(int u)
{
	for(int &i=head[u];i;)
	{
		int v=to[i];
		i=nxt[i];
		dfs(v);
	}
	ans+=(char)(u&255);
}
```
���Է�������д֮��һ����ֻ�ᱻ����һ�Σ���Ϊ�޸�һ�� $i$ �ͻᵼ�¸õ㻹��ϵͳջ�е����� $i$ ȫ���޸ġ�

�����õ���ŷ����·�Ƿ��ģ����Ե������ͺ��ˡ�

����֤��������һ������ $O(n+m)$ ʱ����һ��ŷ����·��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 300010
using namespace std;
int nxt[N<<1],to[N<<1],head[N],cnt;
int deg[N];
void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	deg[u]++,deg[v]--;
}
char str[4];
string ans;
void dfs(int u)
{
	for(int &i=head[u];i;)
	{
		int v=to[i];
		i=nxt[i];
		dfs(v);
	}
	ans+=(char)(u&255);
}
int main()
{
	int n;
	scanf("%d",&n);
	int s=0,t=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		int u=str[1]*256+str[2],v=str[2]*256+str[3];
		add(u,v);
		s=u;
	}
	for(int i=0;i<N-10;i++)
	if(deg[i])
	{
		if(deg[i]>1 || deg[i]<-1){puts("NO");return 0;}
		if(deg[i]==1) s=i;
		if(deg[i]==-1){if(t){puts("NO");return 0;}t=i;}
	}
	dfs(s);
	ans+=char(s/256);
	if(ans.size()!=n+2){puts("NO");return 0;}
	puts("YES");
	reverse(ans.begin(),ans.end());
	cout<<ans;
	return 0;
}
```
