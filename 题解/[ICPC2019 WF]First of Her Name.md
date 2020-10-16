### [链接](https://www.luogu.com.cn/problem/P6257)
倒建SAM，可以发现要求的就是 $endpos$ 集合大小。

直接处理即可。复杂度 $O(n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 2000010
using namespace std;
struct array{
	int* a;
	int& operator [](const short int b){if(a==NULL) a=new int[26],memset(a,0,sizeof(int)*26);return a[b];}
	void operator =(array &b)
	{
		if(b.a==NULL) return;
		if(a==NULL) a=new int[26];
		memcpy(a,b.a,sizeof(int)*26);
	}
}ch[N];

int fa[N],len[N],siz[N],cnt;
int insert(int las,int c)
{
	if(ch[las][c])
	{
		int p=las,np=ch[p][c];
		if(len[p]+1==len[np]) return np;
		else
		{
			int nq=++cnt;
			len[nq]=len[p]+1;
			ch[nq]=ch[np];
			fa[nq]=fa[np],fa[np]=nq;
			for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
			return nq;
		}
	}
	int p=las,u=las=++cnt;
	len[u]=len[p]+1;
	for(;p && !ch[p][c];p=fa[p]) ch[p][c]=u;
	if(!p) fa[u]=1;
	else
	{
		int np=ch[p][c];
		if(len[np]==len[p]+1) fa[u]=np;
		else
		{
			int nq=++cnt;
			len[nq]=len[p]+1;
			ch[nq]=ch[np];
			fa[nq]=fa[np];
			fa[np]=fa[u]=nq;
			for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
		}
	}
	return u;
}
char s[N>>1];
int a[N>>1],b[N],las[N>>1];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	las[0]=cnt=1;
	for(int i=1;i<=n;i++)
	{
		int f;
		scanf("%s%d",s+1,&f);
		las[i]=insert(las[f],s[1]-'A');
		siz[las[i]]++;
	}
    for(int i=1;i<=cnt;i++) a[len[i]]++;
    for(int i=1;i<=n;i++) a[i]+=a[i-1];
    for(int i=1;i<=cnt;i++) b[a[len[i]]--]=i;
    for(int i=cnt;i>1;i--) siz[fa[b[i]]]+=siz[b[i]];
	for(int i=1;i<=k;i++)
	{
		scanf("%s",s+1);
		int m=strlen(s+1),p=1,j=m;
		for(;j>=1 && p && ch[p].a!=NULL;j--) p=ch[p][s[j]-'A'];
		printf("%d\n",!j?siz[p]:0);
	}
	for(int i=1;i<=cnt;i++) delete ch[i].a;
	return 0;
}
```
