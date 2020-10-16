### [链接](https://codeforces.com/problemset/problem/1117/F)
考虑暴力。dfs枚举删掉的字符，然后同时下传删掉的字符串，判断是否可行。

复杂度 $O(\text{能过})$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 100010
#define C 21
using namespace std;
int f[C][C];
vector<int>v;
int n,k;
void solve(int u,vector<int> s)
{
	for(int i=0;i<k;i++)
	if(!((u>>i)&1))
	{
		int can=true,v=u|(1<<i);
		vector<int>t;
		for(int p:s)
		if(p!=i)
		{
			if(!t.empty() && !f[t.back()][p]){can=false;break;}
			t.push_back(p);
		}
		if(!can) continue;
		n=min(n,(int)t.size());
		solve(v,t);
		break;
	}
}
char str[N];
int main()
{
	scanf("%d%d%s",&n,&k,str);
	v.resize(n); 
	for(int i=0;i<n;i++) v[i]=str[i]-'a';
	for(int i=0;i<k;i++)
		for(int j=0;j<k;j++) scanf("%d",&f[i][j]);
	solve(0,v);
	printf("%d",n);
	return 0;
}
```
