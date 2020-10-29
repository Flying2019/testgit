#include<iostream>
#include<cstdio>
#include<cstring>
#define cil(x) ((x+1)>>1)
#define N 20
#define M N*2
#define mod 100007
using namespace std;
char s[N];
int f[N][N][N];
int F(int l,int r,int k)
{
    int& u=f[l][r][k];
    if(u>=0) return u;
    u=0;
    if(l==r) return u=!k;
    if(s[l]==s[r]) return u=r-l<=1?!k:F(l+1,r-1,k);
    return u=k?(F(l+1,r,k-1)+F(l,r-1,k-1))%mod:0;
}
int n;
struct matrix{
    int a[M][M];
    int* operator [](int b){return a[b];}
    matrix(){memset(a,0,sizeof(a));}
    friend matrix operator *(matrix a,matrix b)
    {
        matrix c;
        for(int i=1;i<=n;i++)
            for(int k=i;k<=n;k++)
                for(int j=k;j<=n;j++) c[i][j]=a[i][k]*b[k][j]%mod;
        return c;
    }
}a,b,r;
matrix ksm(matrix a,int k)
{
    matrix o;for(int i=0;i<=n;i++) o[i][i]=1;
    for(;k;k>>=1)
    {
        if(k&1) o=o*a;
        a=a*a;
    }
    return o;
}
int res[N];
int main()
{
    int m;
    scanf("%s%d",s+1,&m);
    int len=strlen(s+1),n=m+cil(m);
    for(int i=0;i<m;i++)
    {
        int r=0;
        for(int j=1;j<=m;j++) r+=F(i,j,j)+(j!=m && s[j]==s[j+1]?F(i,j,j+1):0);
        if(i){a[i][n-cil(m-i)]=r,a[i][i]=24;if(i==1) res[i]=1;else a[i-1][i]=1;}
        else
        {
            res[m]=r,a[n][n]=26;
            for(int j=m;j<n;j++) g[j][j+1]=1,g[j][j]=25;
        }
    }
    if((len+m)&1)
    {
        for(int i=1;i<=n;i++)
    }
	if ((n + m) & 1) {
		for (int i = 1; i <= k; i++) F[i] = f[i];
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++)
				G[i][j] = g[i][j];
	}
	ksm(ceil(n + m));
	if (!((n + m) & 1)) return print(f[k]), 0;
	modint ans = f[k];
	for (int i = 1; i <= k; i++) f[i] = F[i];
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++)
			g[i][j] = G[i][j];
	for (int i = 0; i < m; i++) {
		modint c;
		for (int j = 1; j <= m; j++)
			if (j != m && s[j] == s[j+1]) c += H(i, j, j + 1);
		if (i) g[i][k-ceil(m-i)] = c;
		else f[m] = c, g[k][k] = 0;
	}
	ksm(ceil(n + m));
	print(ans - f[k]);
    return 0;
}