#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long long ll;

template<class T> void read(T &x){
	int f=0; x=0; char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f|=(ch=='-');
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	if(f) x=-x;
}

const int N=200005;
const ll inf=2e18,lim=4e10;
struct L{
	ll k,b;
	L(ll _k=0,ll _b=-inf):k(_k),b(_b){}
	ll operator () (ll x){ return k*x+b; }
};
struct seg{
	L x; seg *lc,*rc;
	seg():x(){ lc=rc=0; }
	void ins(L y,ll l=0,ll r=lim){
		ll m=(l+r)>>1;
		if(y(m)>x(m)) swap(x,y);
		if(x(l)<y(l)){
			if(!lc) lc=new seg;
			lc->ins(y,l,m);
		}
		else if(x(r)<y(r)){
			if(!rc) rc=new seg;
			rc->ins(y,m+1,r);
		}
	}
	ll qry(ll k,ll l=0,ll r=lim){
		ll res=x(k),m=(l+r)>>1;
		if(k<=m&&lc) res=max(res,lc->qry(k,l,m));
		if(k>m&&rc) res=max(res,rc->qry(k,m+1,r));
		return res;
	}
} T2[N<<2];
struct seg2{
	L x; seg2 *lc,*rc;
	seg2():x(){ lc=rc=0; }
	void ins(L y,ll l=0,ll r=N){
		ll m=(l+r)>>1;
		if(y(m)>x(m)) swap(x,y);
		if(x(l)<y(l)){
			if(!lc) lc=new seg2;
			lc->ins(y,l,m);
		}
		else if(x(r)<y(r)){
			if(!rc) rc=new seg2;
			rc->ins(y,m+1,r);
		}
	}
	ll qry(ll k,ll l=0,ll r=N){
		ll res=x(k),m=(l+r)>>1;
		if(k<=m&&lc) res=max(res,lc->qry(k,l,m));
		if(k>m&&rc) res=max(res,rc->qry(k,m+1,r));
		return res;
	}
} T1[N<<2];

ll ql,qr,qp,qx; L qL;
namespace{
	#define lc (o<<1)
	#define rc (o<<1|1)
	#define mid ((l+r)>>1)
	void ins1(int o,int l,int r){
		T1[o].ins(qL);
		if(l==r) return;
		if(qp<=mid) ins1(lc,l,mid);
		else ins1(rc,mid+1,r);
	}
	ll qry1(int o,int l,int r){
		if(ql<=l&&r<=qr) return T1[o].qry(qx);
		if(qr<=mid) return qry1(lc,l,mid);
		if(mid<ql) return qry1(rc,mid+1,r);
		return max(qry1(lc,l,mid),qry1(rc,mid+1,r));
	}
	void ins2(int o,int l,int r){
		if(ql<=l&&r<=qr) return T2[o].ins(qL);
		if(ql<=mid) ins2(lc,l,mid);
		if(mid<qr) ins2(rc,mid+1,r);
	}
	ll qry2(int o,int l,int r){
		ll res=T2[o].qry(qx);
		if(l==r) return res;
		if(qp<=mid) res=max(res,qry2(lc,l,mid));
		else res=max(res,qry2(rc,mid+1,r));
		return res;
	}
	int T[N<<2];
	void upd(int o,int l,int r,int x,int y,int z){
		if(l==x&&y==r){
			T[o]=max(T[o],z);
			return;
		}
		if(x<=mid) upd(lc,l,mid,x,min(y,mid),z);
		if(mid<y) upd(rc,mid+1,r,max(mid+1,x),y,z);
	}
	int qry(int o,int l,int r,int x){
		int res=T[o];
		if(l==r) return res;
		if(x<=mid) res=max(res,qry(lc,l,mid,x));
		else res=max(res,qry(rc,mid+1,r,x));
		return res;
	}
}

vector<pair<pii,int> > c[N];
int a[N],bd[N],n,K;
ll f[N],s[N];
vi p[N];

void init(){
	set<pii> s;
	rep(i,0,n+1){
		s.insert(mp(i,i));
	}
	rep(i,0,n){
		p[i].pb(n+1);
		for(int k=0;k<p[i].size();k++){
			int x=(k?p[i][k-1]:0),y=p[i][k];
			if(x+1>=y) continue;
			set<pii>::iterator it;
			it=s.lower_bound(mp(x+1,0));
			if(it->se>=y) continue;
			int ly=it->se,lx=it->fi;
			for(;it->se<y;s.erase(it++)){
				c[it->se].pb(mp(mp(x+1,it->fi),i));
				lx=it->fi;
			}
			assert(x<=ly);
			s.insert(mp(x,ly));
			assert(lx<=y);
			s.insert(mp(lx,y));
		}
	}
    return;
}

int main(){
	read(n),read(K);
	rep(i,1,n){
		read(a[i]);
		p[a[i]].pb(i);
		s[i]=s[i-1]+a[i];
	}
	init();
	qL=L(0,0),qp=1,ins1(1,1,n);
	rep(i,1,n){
		REP(k,c[i].size()){
			int a=c[i][k].fi.fi;
			int b=c[i][k].fi.se;
			int mex=c[i][k].se;
			bd[mex]=b;
			upd(1,1,n,1,b,mex);
			int pr=min(n,a+K-1);
			if(i<=pr){
				ql=a,qr=b,qx=mex;
				ll val=qry1(1,1,n);
				ql=i,qr=pr,qL=L(mex,val);
				ins2(1,1,n);
			}
		}
		qp=i,qx=s[i];
		f[i]=qry2(1,1,n);
		if(i>=K){
			int mex=qry(1,1,n,i-K+1);
			ql=i-K+1,qr=bd[mex],qx=mex;
			if(ql<=qr){
				f[i]=max(f[i],qry1(1,1,n)+mex*s[i]);
			}
		}
		if(i<n){
			qp=i+1,qL=L(-s[i],f[i]);
			ins1(1,1,n);
		}
	}
	cout<<f[n]<<endl;
	return 0;
}