#include<iostream>
#include<cstdio>
#include<cstdlib>
#define N 100010
using namespace std;
int ch[N][2],val[N],size[N],rnd[N];
int fa[N],id[N];
int tot;
inline void update(int u){size[u]=size[ch[u][0]]+size[ch[u][1]]+1;}
inline int newnode(int v)
{
	size[++tot]=1;
	val[tot]=v;
	id[v]=tot;
	rnd[tot]=rand();
	return tot;
}
int merge(int x,int y)
{
	if(!x || !y) return x+y;
	if(rnd[x]<rnd[y])
	{
		ch[x][1]=merge(ch[x][1],y);
		fa[ch[x][1]]=x;
		update(x);
		return x;
	}
	else
	{
		ch[y][0]=merge(x,ch[y][0]);
		fa[ch[y][0]]=y;
		update(y);
		return y;
	}
}
void split(int u,int k,int &lt,int &rt,int fal=0,int far=0)
{
	if(u==0){lt=rt=0;return;}
	if(k<=size[ch[u][0]])
	{
		rt=u;
		fa[u]=far;
		split(ch[u][0],k,lt,ch[u][0],fal,u);
	}
	else
	{
		lt=u;
		fa[u]=fal;
		split(ch[u][1],k-size[ch[u][0]]-1,ch[u][1],rt,u,far);
	}
	update(u);
}
int root,lt,mt,rt,st;
bool right_son(int u){return ch[fa[u]][1]==u;}
int find(int id)
{
	int u=id,res=size[ch[id][0]]+1;
	while(u)
	{
		if(right_son(u)) res+=size[ch[fa[u]][0]]+1;
		u=fa[u];
	}
    return res;
}
int num[N];
char opt[8];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]),root=merge(root,newnode(num[i]));
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%s%d",opt,&x);
		if(opt[0]=='T')
		{
		    int k=find(id[x]);
		    split(root,k,lt,rt);
		    split(lt,k-1,lt,mt);
		    root=merge(mt,merge(lt,rt));
		}
		else if(opt[0]=='B')
		{
		    int k=find(id[x]);
		    split(root,k,lt,rt,0);
		    split(lt,k-1,lt,mt,0);
		    root=merge(lt,merge(rt,mt));
		}
		else if(opt[0]=='I')
		{
			int p,k=find(id[x]);
			scanf("%d",&p);
			if(!p) continue;
			if(p>0)
			{
				split(root,k+1,rt,st);
				split(rt,k,mt,rt);
				split(mt,k-1,lt,mt);
				root=merge(lt,merge(rt,merge(mt,st)));
			}
			else
			{
				split(root,k,rt,st);
				split(rt,k-1,mt,rt);
				split(mt,k-2,lt,mt);
				root=merge(lt,merge(rt,merge(mt,st)));
			}
		}
		else if(opt[0]=='A') printf("%d\n",find(id[x])-1);
		else
		{
			split(root,x,lt,rt);
		    int u=lt;
		    while(ch[u][1]) u=ch[u][1];
		    printf("%d\n",val[u]);
		    root=merge(lt,rt);
		}
	}
}
