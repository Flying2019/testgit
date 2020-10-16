### [����](http://codeforces.com/problemset/problem/687/D)
���ȿ���̰�ģ���Ȼ����Ӧ�þ����������ı�ʹ֮���С�������˵�����ǴӴ���С�ӱ�ֱ��ͼ����һ������ͼΪֹ��

����Ȼ����ͨ�����������㡣���������ж��ѯ����ô�죿

���ڱ����������滷����ô����ͼ���Ǳ���һ�����ṹ��Ȼ��ʣ�µı����ϼӼ��ɡ�

������˵���ô�Ȩ���鼯ά�����������ֱ�������Ȼ�����·��ѹ�������Ǻϲ�����ͼֱ������һ��ͺ��ˡ�

Ȼ���������ڱ�����˼·�����ɡ����Ӷ� $O(n^2+q\log m\times \alpha(n))$��

Ȼ�����ڳ������󣬱� $O(nm)$ �ı���ܳ���ˡ�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define M 500010
using namespace std;
struct node{
	int x,y,w,id;
	bool operator <(const node a)const{return w>a.w;}
}r[M];
int f[N*2];
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&r[i].x,&r[i].y,&r[i].w),r[i].id=i;
	sort(r+1,r+m+1);
	while(q --> 0)
	{
		int lf,rf,w=-1;
		scanf("%d%d",&lf,&rf);
		for(int i=1;i<=n*2;i++) f[i]=i;
		for(int i=1;i<=m;i++)
		if(r[i].id>=lf && r[i].id<=rf)
		{
			int hx=find(r[i].x),hy=find(r[i].y),ix=find(r[i].x+n),iy=find(r[i].y+n);
			if(hx==hy || ix==iy) {w=r[i].w;break;}
			f[hx]=iy,f[hy]=ix;
		}
		printf("%d\n",w);
	}
	return 0;
}
```
