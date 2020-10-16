### [����](https://zjusummer.contest.codeforces.com/group/clkkguw3vK/contest/102666/problem/F)
### ��Ŀ����
�� $n$ ���㣬����ÿ�� $0\leq m\leq \frac{n(n-1)}2$���� $n$ ���� $m$ ���ߵ���ͨ��������
### ���
���ȿ��ǲ���ͨ��������� $g_{n,m}$ ��ʾ $n$ ���� $m$ ���ߵķ���������Ȼ�� $\displaystyle g_{n,m}=\binom{\frac{n(n-1)}{2}}{m}$��

���������Ǵ𰸣������� $f_{n,m}$ ��ʾ $n$ ���� $m$ ���ߵ���ͨ�鷽���������Է����� 
$$f_{n,m}=g_{n,m}-\sum_{i=1}^{n-1}\binom{n-1}{i-1}\sum_{j=1}^{m}f_{i,j}\times g_{n-i,m-j}$$

�������ɣ�ȫ����ͨ�ķ����������з�������ȥ��ȫ��ͨ�ķ�����������ȫ��ͨ���Կ���ǿ�л��� $i$ ���� $j$ ���ߵ���ͨ�顣

Ȼ��ֱ�Ӽ�������ʽ���� $O(n^5)$��

���Է��ֺ����Ǹ�ʽ����һ�������ʽ��ֱ��NTT��$O(n^4\log n)$��

���ǻ�T������������û��Ҫÿ�ζ����� $\text{DFT}$ �� $\text{IDFT}$��ֱ�ӱ��� $f_{i,j}$ �� $\text{DFT}$ ��ʽ���ɡ�

���ڻ����е�������Ҫ��һ�³����ܹ���

���Ӷ� $O(n^4)$��
```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#define N 110
#define M 20010
#define G 3
#define mod 998244353
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define Gi (mod+1)/G
using namespace std;
int rev[M];
int get_rev(int n)
{
	int lim=1,l=0;
	while(lim<=n*2) lim<<=1,l++;
	for(int i=1;i<lim;i++)
	rev[i]=rev[i>>1]>>1|((i&1)<<(l-1));
	return lim;
}
int ksm(int a,int b=mod-2)
{
	int r=1;
	for(;b;b>>=1)
	{
		if(b&1) r=1ll*r*a%mod;
		a=1ll*a*a%mod;
	}
	return r;
}
void ntt(int f[],int lim,int opt)
{
	for(int i=0;i<lim;i++)
	if(i<rev[i]) swap(f[i],f[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		int r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
		for(int i=0;i<lim;i+=mid<<1)
			for(int j=0,o=1;j<mid;j++,o=1ll*o*r%mod)
			{
				int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
				f[i+j]=(x+y)%mod;
				f[i+j+mid]=(x-y+mod)%mod;
			}
	}
	if(opt==-1)
	{
		int inv=ksm(lim);
		for(int i=0;i<lim;i++) f[i]=1ll*f[i]*inv%mod;
	}
}
int f[N][M],g[N][M],h[M],fac[M],inv[M];
int calc(int n){return n*(n-1)/2;}
int C[N][N];
inline int Cf(int x,int y){return y==0?1:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main()
{
    int n;
    scanf("%d",&n);
    int m=calc(n);
    fac[0]=1;
	C[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        C[i][0]=1;
    	for(int j=1;j<=n;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
    for(int i=1;i<=m;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[m]=ksm(fac[m]);
    for(int i=m-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=calc(i);j++) g[i][j]=Cf(calc(i),j);
    int lim=get_rev(m);
    for(int i=1;i<=n;i++) ntt(g[i],lim,1);
    for(register int i=1;i<=n;i++)
    {
        for(register int j=0;j<lim;j++) f[i][j]=g[i][j],h[j]=0;
        for(register int j=0;j<lim;j++)
        	for(register int t=1;t<i;t++) h[j]=(h[j]+1ll*C[i-1][t-1]*f[t][j]%mod*g[i-t][j])%mod;
        for(register int j=0;j<lim;j++) f[i][j]=(f[i][j]-h[j]+mod)%mod;
    }
    ntt(f[n],lim,-1);
    for(int i=0;i<=m;i++) printf("%d\n",f[n][i]);
	// printf("%d",clock());
    return 0;
}
```
