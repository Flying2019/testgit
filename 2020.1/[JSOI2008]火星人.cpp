#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
#define N 200010
#define ull unsigned long long
const ull base=43;
ull bases[N];
struct Ftreap{
	int ch[N][2],siz[N],rnd[N];
	ull val[N],sum[N];
	int tot;
	inline void update(int u)
	{
		siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;
		sum[u]=sum[ch[u][0]]*bases[siz[ch[u][1]]+1]+val[u]*bases[siz[ch[u][1]]]+sum[ch[u][1]];
	}
	inline int new_node(ull v)
	{
		siz[++tot]=1;
		sum[tot]=val[tot]=v;
		ch[tot][0]=ch[tot][1]=0;
		rnd[tot]=rand();
		return tot;
	}
	int merge(int x,int y)
	{
		if(!x || !y) return x+y;
		if(rnd[x]<rnd[y])
		{
			ch[x][1]=merge(ch[x][1],y);
			update(x);
			return x;
		}
		else
		{
			ch[y][0]=merge(x,ch[y][0]);
			update(y);
			return y;
		}
	}
	void split(int u,int k,int &lt,int &rt)
	{
		if(u==0){lt=rt=0;return;}
		if(siz[ch[u][0]]<k)
		{
			lt=u;
			split(ch[u][1],k-siz[ch[u][0]]-1,ch[u][1],rt);
		}
		else
		{
			rt=u;
			split(ch[u][0],k,lt,ch[u][0]);
		}
		update(u);
	}
	int lt,rt,mt;
	ull answer(int &root,int l,int r)
	{
		split(root,l-1,lt,mt);
		split(mt,r-l+1,mt,rt);
		ull ans=sum[mt];
		root=merge(lt,merge(mt,rt));
		return ans;
	}
	void insert(int &root,int p,ull v)
	{
		split(root,p,lt,rt);
		root=merge(lt,merge(new_node(v),rt));
	}
	void erase(int &root,int p)
	{
		split(root,p,lt,rt);
		split(lt,p-1,lt,mt);
		mt=merge(ch[mt][0],ch[mt][1]);
		root=merge(lt,merge(mt,rt));
	}
}t;
int n,root;
char str[N],opt[2];
int lcp(int x,int y)
{
	int l=1,r=min(n-x+1,n-y+1),ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(t.answer(root,x,x+mid-1)==t.answer(root,y,y+mid-1)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	return ans;
}
int main()
{
	srand(19260817);
	scanf("%s",str+1);
	int m;
	scanf("%d",&m);
	n=strlen(str+1);
	bases[0]=1;
	for(int i=1;i<=100000;i++) bases[i]=bases[i-1]*base;
	for(int i=1;i<=n;i++) root=t.merge(root,t.new_node(str[i]-'a'+1));
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%s%d",opt,&x);
		if(opt[0]=='Q')
		{
			scanf("%d",&y);
			printf("%d\n",lcp(x,y));
		}
		else if(opt[0]=='R')
		{
			scanf("%s",opt);
			t.erase(root,x);
			t.insert(root,x-1,opt[0]-'a'+1);
		}
		else if(opt[0]=='I')
		{
			scanf("%s",opt);
			t.insert(root,x,opt[0]-'a'+1);
			n++;
		}
	}
	return 0;
}

