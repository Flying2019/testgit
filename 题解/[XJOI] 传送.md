### [����](http://115.236.49.52:83/contest/1523/problem/2)
�������û�б�ban���ĵ���ô����

���ȿ����г����� $f_{i,j}=\sum_{k}{f_{i-1,j-a_k}}$���� $\sum{f_{n,i},\ i\bmod l=0}$��

������ $a_i$ �����ɺ��� $g(x)=\sum_i x^{a_i}$����ô $f^i(j+k)=\sum_{j,k}{f^{i-1}(j)\times g(k)}$

�����������һ��ѭ���������ʽ��������Ŀ��ǡ���� $n$ ��һ�� $2^k$ ����ʽ��ֱ������ $\text{NTT}$ ���Ͽ����ݴ����ɡ�

������ban���ĵ���ô�������Է��֣����ǿ������������������֮��ķ�������

���ǲ����� $f_{i,j}$ ��ʾ $i\rightarrow j$ �ķ�������$g_{i,j}$ ��ʾ $i\rightarrow j$ �Ҳ�����������ban��ķ�������

��Ȼ��
$$g_{i,j}=f_{i,j}-\sum_{k\in(i,j)}g_{i,k}\times f_{k,j}$$

������˵�����������еķ�������ȥ����������ban�㡣�ݳ�һ�¼��ɡ�

���Ӷ� $O(m^2\times n\log n)$������ͨ�����⡣

����һ�� $O(m\times n\log n)$ ����������ÿ��������һ����ban�ĵ㣬����ʱ��Ӧλ�õ�ֵɾ�����ɡ�
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 400010
#define mod 998244353
#define G 3
#define Gi ((mod+1)/G)
using namespace std;
int ksm(int a,int b)
{
    int ans=1;
    for(;b;b>>=1)
    {
        if(b&1) ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
    }
    return ans;
}
int f[N],g[N],swp[N];
int rev[N];
int get_rev(int n)
{
	int l=0,lim=1;
	while(lim<n) lim<<=1,l++;
	for(int i=0;i<lim;i++)
	rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	return lim;
}
void ntt(int f[],int lim,int opt)
{
    for(int i=0;i<lim;i++)
    if(i<rev[i]) swap(f[i],f[rev[i]]);
    for(int mid=1;mid<lim;mid<<=1)
    {
        int r=ksm(opt==1?G:Gi,(mod-1)/(mid*2));
        for(int i=0;i<lim;i+=mid<<1)
        {
            int o=1;
            for(int j=0;j<mid;j++,o=1ll*o*r%mod)
            {
                int x=f[i+j],y=1ll*f[i+j+mid]*o%mod;
                f[i+j]=1ll*(x+y)%mod;
                f[i+j+mid]=1ll*(x-y+mod)%mod;
            }
        }
    }
    if(opt==-1)
    {
        int ni=ksm(lim,mod-2);
        for(int i=0;i<lim;i++) f[i]=1ll*f[i]*ni%mod;
    }
}
#define M 17
struct ban{
    int x,y;
    bool operator <(const ban a)const{return x<a.x;}
}bn[M];
int num[N],fn[M][M],gn[M][M];
int main()
{
    int n,l,m;
    scanf("%d%d%d",&n,&l,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&bn[i].x,&bn[i].y);
    bn[0].x=0,bn[0].y=0;
    bn[++m].x=l,bn[0].y=0;
    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++) scanf("%d",&num[i]),f[num[i]]++;
    int lim=get_rev(n);
    ntt(f,n,1);
    sort(bn,bn+m+1);
    for(int i=0;i<=m;i++)
        for(int j=i+1;j<=m;j++)
        {
            for(int k=0;k<n;k++) g[k]=ksm(f[k],bn[j].x-bn[i].x);
            ntt(g,lim,-1);
            fn[i][j]=g[(bn[j].y-bn[i].y+n)%n];
        }
    for(int i=m;i>=0;i--)
        for(int j=i+1;j<=m;j++)
        {
            gn[i][j]=fn[i][j];
            for(int k=i+1;k<j;k++) gn[i][j]=(gn[i][j]-1ll*gn[i][k]*fn[k][j]%mod+mod)%mod;
        }
    printf("%d\n",gn[0][m]);
    return 0;
}
```
