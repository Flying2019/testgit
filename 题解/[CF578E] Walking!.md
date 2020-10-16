### [链接](https://codeforces.com/problemset/problem/578/E)
贪心+STL。

考虑一种贪心：我们每次不停往后选，直到选不出合适为止，然后再往前选。

但是这样会出问题，因为有时候这样会导致前后连不上，导致答案变大。所以考虑一种策略：即这种情况下如果当前前面还有未匹配的点，我们优先折回去匹配。

复杂度 $O(n\log n )$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 100010
using namespace std;
char str[N];
set<int>s[2];
int ans[N],ta;
int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1);
	for(int i=1;i<=n;i++) s[str[i]=='L'].insert(i);
	s[0].insert(n+1),s[1].insert(n+1);
	if(s[0].size()<s[1].size() || (s[0].size()==s[1].size() && *s[0].begin()>*s[1].begin())) swap(s[0],s[1]);
	bool p=0;
	int cnt=0,pos=-1,nxt=*s[0].begin();
	for(int i=1;i<=n;i++,p=!p)
	{
		if(nxt>n || (*s[!p].lower_bound(nxt)>n && *s[p].begin()!=nxt && *s[p].begin()<*s[!p].begin())) nxt=*s[p].begin(),++cnt;
		pos=nxt;
		s[p].erase(pos);
		nxt=*s[!p].lower_bound(pos);
		ans[++ta]=pos;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=ta;i++) printf("%d ",ans[i]);
	return 0;
}
```
