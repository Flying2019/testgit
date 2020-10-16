#include<iostream>
#include<cstdio>
#include<cstring>
#define N 25010
#define M 410
#define ll long long
#define mod 1000000007
using namespace std;
int num[N],n,m,k;
int cnt[N];
ll ksm(ll a,ll b=mod-2)
{
	ll ans=1;
	for(;b;b>>=1)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
bool is_colorful()
{
	if(m<k) return false;
	int res=0;
	for(int i=1;i<=m;i++)
	{
		if(i>k) res-=(--cnt[num[i-k]])<=0;
		res+=(++cnt[num[i]])==1;
		if(res==k) return true;
	}
	return false;
}
bool have_same()
{
	if(m>k) return true;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=m;i++)
	if(cnt[num[i]]++) return true;
	return false;
}
ll f[N][M],g[N][M],fac[N],inv[N];
ll sf[M],sg[M];
ll work1()
{
	sf[0]=sg[0]=f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=min(i,k);j++)
		{
			f[i][j]=(f[i][j]+sf[j]+f[i-1][j-1]*(k-j+1)%mod)%mod;
			g[i][j]=(g[i][j]+sg[j]+g[i-1][j-1]*(k-j+1)%mod)%mod;
			if(j>=m) g[i][j]=(g[i][j]+f[i][j])%mod;
		}
		for(int j=k-1;j>=0;j--)
		sf[j]=(sf[j+1]+f[i][j])%mod,sg[j]=(sg[j+1]+g[i][j])%mod;
	}
	ll ans=0;
	for(int i=1;i<k;i++) ans=(ans+g[n][i])%mod;
	return ans*fac[k-m]%mod*inv[k]%mod;
}
ll C(int a,int b){return b>a?0:fac[a]*inv[b]%mod*inv[a-b]%mod;}
ll work2()
{
	sf[0]=f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=min(i,k);j++) f[i][j]=(f[i][j]+sf[j]+f[i-1][j-1]*(k-j+1)%mod)%mod;
		sf[k]=0;
		for(int j=k-1;j>=0;j--) sf[j]=(sf[j+1]+f[i][j])%mod;
	}
	memset(cnt,0,sizeof(cnt));
	int l,r;
	for(l=1;l<=m;l++) if(cnt[num[l]]++) break;
	--l;
	memset(cnt,0,sizeof(cnt));
	for(r=m;r;r--) if(cnt[num[r]]++) break;
	r=m-r;
	ll ans=0;
	for(int i=l;i+m-l<=n;i++)
	{
		ll res1=0,res2=0;
		for(int j=l;j<k;j++) res1=(res1+f[i][j]*fac[k-j]%mod*inv[k]%mod*C(k-l,j-l)%mod*fac[j-l]%mod)%mod;
		for(int j=r;j<k;j++) res2=(res2+f[n-(i-l+m)+r][j]*fac[k-j]%mod*inv[k]%mod*C(k-r,j-r)%mod*fac[j-r]%mod)%mod;
		ans=(ans+res1*res2%mod)%mod;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=m;i++) scanf("%d",&num[i]);
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	ll ans=ksm(k,n-m)*(n-m+1)%mod;
	if(is_colorful()){printf("%lld\n",ans);return 0;}
	if(have_same()){printf("%lld\n",(ans-work2()+mod)%mod);return 0;}
	printf("%lld\n",(ans-work1()+mod)%mod);
	return 0;
}

