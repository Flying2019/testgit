### [链接](http://codeforces.com/contest/551/problem/E)
看到查询某种数字中最远的两个数字，可以发现这等同于找最小和最大的数字。很容易想到用set。

但是这样很难处理区间加的情况。看到 $m$ 不大，考虑从根号算法入手。

具体来说，我们将整个区域分块，对于查询，如果一个块中不存在当前值，我们就不必查找这个块了。而这个恰好可以用无序表完成。

考虑修改。对于一次块内的修改，可以直接打tag。而对于块外可以重构无序表。这样单次时间复杂度是 $O(\sqrt{n})$ 的。

总时间复杂度 $O(m\sqrt{n})$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
#define N 500010
#define B 810
#define ll long long
using namespace std;
unordered_set<ll>s[N];
ll tg[N],a[N];
int bl[N],br[N];
int fl[N],fr[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fl[i]=n+1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		bl[i]=(i-1)/B;
		fl[bl[i]]=min(fl[bl[i]],i);fr[bl[i]]=max(fr[bl[i]],i);
		s[bl[i]].insert(a[i]);
	}
	bl[n+1]=-1;
	int bm=n/B;
	while(m --> 0)
	{
		int opt;
		ll l,r,x;
		scanf("%d%lld",&opt,&l);
		if(opt==1)
		{
			scanf("%lld%lld",&r,&x);
			if(bl[l]==bl[r])
			{
				s[bl[l]].clear();
				for(int i=l;i<=r;i++) a[i]+=x;
				for(int i=fl[bl[l]];i<=fr[bl[l]];i++) s[bl[l]].insert(a[i]);
				continue;
			}
			s[bl[l]].clear();
			for(int i=l;i<=fr[bl[l]];i++) a[i]+=x;
			for(int i=fl[bl[l]];i<=fr[bl[l]];i++) s[bl[l]].insert(a[i]);
			for(int i=bl[l]+1;i<=bl[r]-1;i++) tg[i]+=x;
			s[bl[r]].clear();
			for(int i=fl[bl[r]];i<=r;i++) a[i]+=x;
			for(int i=fl[bl[r]];i<=fr[bl[r]];i++) s[bl[r]].insert(a[i]);
		}
		else
		{
			int pl=0,pr=0;
			for(int i=0;i<=bm;i++)
			if(s[i].find(l-tg[i])!=s[i].end())
			{
				for(int j=fl[i];j<=fr[i];j++)
				if(a[j]==l-tg[i]){pl=j;break;}
				break;
			}
			if(!pl){puts("-1");continue;}
			for(int i=bm;i>=0;i--)
			if(s[i].find(l-tg[i])!=s[i].end())
			{
				for(int j=fr[i];j>=fl[i];j--)
				if(a[j]==l-tg[i]){pr=j;break;}
				break;
			}
			if(pl>pr){printf("%d %d\n",pl,pr);throw;}
			printf("%d\n",pr-pl);
		}
	}
	return 0;
}
```
