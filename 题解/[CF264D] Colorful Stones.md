### [����](http://codeforces.com/problemset/problem/264/D)
��ֵ��ַ���ƥ�䡣

�����õ� $(x,y)$ ��ʾ�����ַ����е�һ��ƥ�䵽 $x$���ڶ���ƥ�䵽 $y$����ô��ͱ����һ�Ŷ�ά��ͼ��

����ʲô����»ᵼ��ĳ���㲻�ɴ���Է��֣�������� $\texttt{RG},\texttt{GR}$ �����Ĵ�����ô��������һ�����ɴ�ĵ㡣

���Է���ֻ����������ᵼ��**�õ�**���ɴҲ����˵һ���� $(x,y)$ ���ɴ��ôһ��û��һ�� $(x-1,y-1)\rightarrow (x,y)$ �ıߡ�

Ҳ����˵������ʣ�µĵ㣬���ǿ���ֱ��̰�Ĵ���ά��һ��ǰ׺�ͼ��ɡ�

���Ӷ� $O(n)$��
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 1000010
using namespace std;
char str[N];
int s[N],t[N];
ll ans;
int f[N][8];
inline int sv(int x,int y){return (x>y)*4+x+y;}
int main()
{
	int n,m;
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++) s[i]=str[i]=='R'?0:(str[i]=='G'?1:2);
	for(int i=2;i<=n+1;i++)
	{
		memcpy(f[i],f[i-1],sizeof(f[i]));
        if(i<=n && s[i-1]!=s[i]) f[i][sv(s[i-1],s[i])]++;
	}
	scanf("%s",str+1);
	m=strlen(str+1);
	for(int i=1;i<=m;i++) t[i]=str[i]=='R'?0:(str[i]=='G'?1:2);
	int l=1,r=1;
	for(int i=1;i<=m;i++)
	{
		if(i>1 && t[i]!=t[i-1]) ans-=f[r][sv(t[i],t[i-1])]-f[l][sv(t[i],t[i-1])];
		for(;r<=n && s[r]!=t[i];r++);ans+=r-l+(r<=n);
		if(r<=n) ++r;
		if(l<r && s[l]==t[i]) ++l;
	}
	printf("%lld\n",ans);
	return 0;
}
```
