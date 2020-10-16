### [����](https://www.luogu.com.cn/problem/AT5693)
����̰�ġ����Է��֣����ĳ��������������ǰ $p$ ����ô������������һ�����Խ���ǰ $p$ ��������Ȼ�ȴӴ�С����

��ô������ô�ж�һ�����ܷ����ǰ $p$ �����ȣ���� $a_i-a_p>m$����Ȼ $i$ ��ûϷ�ˡ�

�ٿ���������㣬���� $n-i\geq v$����Ȼֱ��ȡ��֮��� $v$ �����ɡ�

�ٿ��������������Ϊ���ò���������ĵ����һЩ������Ȼϣ����Щ�������� $a_p$ �����Կ��ǽ���Щ�ӵ������䵽ÿ�����ϣ�ʹ $a_p$ �� $a_{i-1}$ ������ƽ����Ȼ���жϼ��ɡ�

���Ӷ� $O(n)$��
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 200010
#define ll long long
using namespace std;
ll num[N],n,q,l,r;
struct node{
	ll opt,x,s,t;
}p[N];
short int check(ll x)
{
	for(int i=1;i<=q;i++)
	{
		if(p[i].opt==1 && x>=p[i].x) x=(x+p[i].s)*p[i].t;
		else if(p[i].opt==2 && x<=p[i].x) x=(x-p[i].s)/p[i].t;
	}
	if(x<l) return -1;
	if(x>r) return 1;
	return 0;
}
int main()
{
	scanf("%lld%lld%lld%lld",&n,&q,&l,&r);
	for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
	sort(num+1,num+n+1);
	for(int i=1;i<=q;i++)
	scanf("%lld%lld%lld%lld",&p[i].opt,&p[i].x,&p[i].s,&p[i].t);
	int l=1,r=n,p=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int t=check(num[mid]);
		if(t==1) r=mid-1;
		else if(t==-1) l=mid+1;
		else{p=mid;break;}
	}
	if(!p){puts("0");return 0;}
	l=p+1,r=n;
	int rf=p;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(num[mid])==0) l=mid+1,rf=mid;
		else r=mid-1;
	}
	l=1,r=p-1;
	int lf=p;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(num[mid])==0) r=mid-1,lf=mid;
		else l=mid+1;
	}
	printf("%d\n",rf-lf+1);
	return 0;
}
```
