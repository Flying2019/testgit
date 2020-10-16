### [����](https://atcoder.jp/contests/joisc2014/tasks/joisc2014_c)[_](https://www.luogu.com.cn/problem/AT1219)
�����������������������������û��log�����ģ������������ŷ����롣

����ѯ�����ߣ�����ֱ��Ī�����Ǻ��Ѵ���ɾ��һ�����Ĳ���������һ�������Ī�ӣ��ع�Ī�ӡ�

���ǰ�Ī�ӵķ�ʽ�������������ѯ�ʵ���˵������һ�����У���˵�Ĳ���ڿ鳤����ô�����Ҷ˵㵥�����������ǿ��Ժܷ���شӸÿ�����Ҷ�ֻͨ�������������õ��𰸡�

���仰˵��һ��ʼ��ʼ�����Ҷ˵���λ�ڸÿ����Ҷ˵Ŀ����䡣Ȼ�����ÿ��ѯ�ʣ��Ƚ��Ҷ˵���ֵѯ�������Ҷ˵㣬Ȼ���¼�µ�ǰֵ��

�����ƶ���˵�Ĺ��̣���¼�����޸���Ϣ���ƶ����֮�����ƶ���˵�ʱ���޸���Ϣ��ͬʱ��˵��λ�����Ҷˣ�ע���Ҷ˵㲻�ؽ��г�����

�ر�ģ����������Ҷ˵���ͬһ���ڣ�����ֱ�ӱ��������ɡ�

������������˵㲻��ͬһ����ʱ�����Ǳ���������飬���¼��㡣���ڿ���� $O(\sqrt{n})$ ��������ʱ�临�Ӷ��ǶԵġ�

��ʱ�临�Ӷ� $O((n+m)\sqrt{n})$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
ll a[N],p[N],ans[N];
int cnt[N];
ll maxn,pmaxn;
int qt[N],pt;
void save(){pmaxn=maxn;pt=0;}
void add(int x){qt[++pt]=a[x];cnt[a[x]]++,maxn=max(maxn,p[a[x]]*cnt[a[x]]);}
void back(){while(pt) --cnt[qt[pt--]];maxn=pmaxn;}
int bl[N];
struct ques{
	int l,r,id;
	bool operator <(const ques a)const{return bl[l]==bl[a.l]?r<a.r:bl[l]<bl[a.l];}
}q[N];
int sq[N];
int main()
{
	int n,m;
	int B=233;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[i]=a[i],bl[i]=i/B;
	sort(p+1,p+n+1);
	int tn=unique(p+1,p+n+1)-p-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(p+1,p+tn+1,a[i])-p;
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int l=0,r=0;
	for(int i=1;i<=m;i++)
	{
		if(i==1 || bl[q[i].l]!=bl[q[i-1].l]){for(int j=1;j<=n;j++) cnt[j]=0;maxn=pmaxn=0;l=min(bl[q[i].l]*B+B,n);r=l-1;}
		if(bl[q[i].l]==bl[q[i].r])
		{
			ll res=0;
			for(int j=q[i].l;j<=q[i].r;j++)
			sq[a[j]]++,res=max(res,1ll*p[a[j]]*sq[a[j]]);
			ans[q[i].id]=res;
			for(int j=q[i].l;j<=q[i].r;j++)
			sq[a[j]]--;
			continue;
		}
		while(r<q[i].r) add(++r);
		save();while(l>q[i].l) add(--l);
		ans[q[i].id]=maxn;
		back();
		l=min(bl[q[i].l]*B+B,n);
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
/*
10 10
1 2 1 1 2 2 1 1 1 2
1 5
2 4
2 7
4 8
3 6
2 9
4 10
2 7
1 10
7 10
*/
```
