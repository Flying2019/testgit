### [链接](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102643/problem/C)
### 题目大意

### 题解
暴力跑得飞快的题目。。。

考虑一个暴力：把每条点能直接到的点用邻接表存，每次暴力判断，复杂度 $O(n^2)$。

考虑优化：邻接表不是01矩阵吗？bitset套上，复杂度 $O(\frac{n^2}{\omega})$，空间会炸。

考虑再优化：$m$ 与 $n$ 同阶，是不是不用存那么多？考虑每个bitset分成 $\sqrt{N}$ 块，每块只有用到才激活，空间复杂度 $O(\frac{n^{1.5}}{\omega})$。

但是某OJ上卡空间，被卡MLE了。考虑继续优化，可以发现有另一种 $O(deg_u+deg_v)$ 的暴力。考虑如果某个点连的边比较少，那么就直接暴力访问邻接表，否则采用上述方法。空间复杂度 $O(\text{能过})$。（好像前面那种优化没啥用）
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<bitset>
#include<vector>
#define N 120000
#define M 512
#define B N/M+2
#define bt bitset<M>
using namespace std;
struct bbit{
	vector<bt > num;
	int v[B];
	bbit():num(0){memset(v,0,sizeof(v));}
	void insert(int u)
	{
		int p=u/M;
		if(v[p]) num[v[p]-1][u-p*M]=1;
		else
		{
			v[p]=num.size()+1;
			num.push_back(bt(0));
			num[v[p]-1][u-p*M]=1;
		}
	}
	bool find(int u)
	{
		int p=u/M;
		if(v[p]) return num[v[p]-1][u-p*M];
		else return false;
	}
};
vector<bbit>g;
vector<int>rd[N];
int id[N];
bool vis[N];
int main()
{
	memset(id,-1,sizeof(id));
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(id[u]==-1) rd[u].push_back(v);
			else g[id[u]].insert(v);
			if(id[v]==-1) rd[v].push_back(u);
			else g[id[v]].insert(u);
			if(rd[u].size()>=B && id[u]==-1)
			{
				id[u]=g.size();
				g.push_back(bbit());
				for(int t:rd[u])
				g[id[u]].insert(t);
			}
			if(rd[v].size()>=B && id[v]==-1)
			{
				id[v]=g.size();
				g.push_back(bbit());
				for(int t:rd[v])
				g[id[v]].insert(t);
			}
		}
		else if(opt==2)
		{
			bool righ=false;
			int u,v;
			scanf("%d%d",&u,&v);
			if(id[v]==-1) swap(u,v);
			if(id[u]==-1 && id[v]==-1)
			{
				for(int j:rd[u])if(j==v){puts("No");righ=true;break;}
				if(righ) continue;
				for(int j:rd[u]) vis[j]=true;
				for(int j:rd[v])if(vis[j]){puts("Yes");righ=true;break;}
				if(!righ) puts("No");
				for(int j:rd[u]) vis[j]=false;
				continue;
			}
			if(id[u]==-1)
			{
				for(int j:rd[u])
				if(g[id[v]].find(j)){puts("Yes");righ=true;break;}
				if(!righ) puts("No");
				continue;
			}
			if(g[id[u]].find(v)){puts("No");continue;}
			for(int j=0;j<B;j++)
			if(g[id[u]].v[j] && g[id[v]].v[j])
			{
				if((g[id[u]].num[g[id[u]].v[j]-1]&g[id[v]].num[g[id[v]].v[j]-1]).any())
				{
					puts("Yes");
					righ=true;
					break;
				}
			}
			if(!righ) puts("No");
		}
	}
	return 0;
}
```
