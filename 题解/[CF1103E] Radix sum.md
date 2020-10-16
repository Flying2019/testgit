### [链接](https://codeforces.com/problemset/problem/1103/E)
首先如果不考虑模数，可以发现这就是一个 $k$ 进制下的循环卷积，和 $FWT$ 中的 $xor$ 十分类似。

虽然找不到 10 在 $2^{58}$ 下的原根，但是明显可以发现 $gcd(5^5,{2^{58}})=1$，所以我们考虑构造 $5$ 进制，最后再处理。

考虑构造一个 $\omega_5$ 作为单位根。由于模数很奇怪，并不能得到 $\omega_5$ 在模意义下的精确值。但是我们根据单位根的性质找到分圆多项式 $Φ_5(x)=x^4+x^3+x^2+x+1$。由此可以基本确定 $\omega_5$。

再仿照 $FWT$，同理易得 $k$ 进制下的循环卷积公式。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
#define N 100000
#define L 10
using namespace std;
struct compl_{
	#define P 5
	ull a[P];
	compl_(ull A=0,ull B=0,ull C=0,ull D=0,ull E=0){a[0]=A,a[1]=B,a[2]=C,a[3]=D,a[4]=E;}
	ull& operator [](int i){return a[i];}
	compl_ operator +(compl_ b){return compl_(a[0]+b[0],a[1]+b[1],a[2]+b[2],a[3]+b[3],a[4]+b[4]);}
	compl_ operator -(compl_ b){return compl_(a[0]-b[0],a[1]-b[1],a[2]-b[2],a[3]-b[3],a[4]-b[4]);}
	compl_ operator *(compl_ b)
	{
		compl_ c;
		for(int i=0;i<P;i++)
		if(a[i]) for(int j=0;j<P;j++)
				if(b[j]) c[(i+j)%P]+=a[i]*b[j];
		return c;
	}
	compl_ operator *(int p)
	{
		compl_ c;
		for(int i=0;i<P;i++) c[(p+i)%5]=(p&1)?-a[i]:a[i];
		return c;
	}
}f[N];
compl_ ksm(compl_ a,ull b)
{
	compl_ r(1);
	for(;b;b>>=1){if(b&1) r=r*a;a=a*a;}
	return r;
}
void fft(compl_ f[],int opt)
{
	for(int mid=1;mid<N;mid*=L)
	{
		for(int p=0;p<N;p++)
		if(p/mid%L==0)
		{
			compl_ swp[L];
			for(int i=0;i<L;i++)
				for(int j=0;j<L;j++)
				swp[i]=swp[i]+(f[p+j*mid]*((ull)i*j*(opt==1?1:L-1)%L));
			for(int i=0;i<L;i++) f[p+i*mid]=swp[i];
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		f[a][0]++;
	}
	fft(f,1);
	for(int i=0;i<N;i++) f[i]=ksm(f[i],n);
	fft(f,-1);
	ull inv5=6723469279985657373ull;
	for(int i=0;i<n;i++)
	{
		ull res=(f[i][0]-f[i][4])*inv5/32ull%(1ull<<58);
		cout<<res<<endl;
	}
	return 0;
}
```
