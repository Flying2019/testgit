#include<iostream>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 500010
using namespace std;
struct PAM{
	int len[N],nxt[N],ch[N][30],val[N],cnt;
	int root0,root1,last;
	PAM(void)
	{
		cnt=-1;
		last=root0=++cnt;
		root1=++cnt;
		len[root0]=0,nxt[root0]=root1;
		len[root1]=-1,nxt[root1]=root1;
	}
	void insert(int c,int l,char str[])
	{
		int p=last;
		for(;str[l-len[p]-1]!=str[l];p=nxt[p]) continue;
		if(!ch[p][c])
		{
			int q=++cnt,np=nxt[p];
			len[q]=len[p]+2;
			for(;str[l-len[np]-1]!=str[l];np=nxt[np]) continue;
			nxt[q]=ch[np][c];
			ch[p][c]=q;
		}
		last=ch[p][c];
		val[last]++;
	}
}t1,t2;
ll ans;
void dfs(int r1,int r2)
{
	if(r1+r2>2) ans=ans+1ll*t1.val[r1]*t2.val[r2];
	for(int i=1;i<=26;i++)
	if(t1.ch[r1][i] && t2.ch[r2][i])
	dfs(t1.ch[r1][i],t2.ch[r2][i]);
}
char s1[N],s2[N];
int main()
{
	scanf("%s%s",s1+1,s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);
	for(int i=1;i<=n;i++) t1.insert(s1[i]-'A'+1,i,s1);
	for(int i=1;i<=m;i++) t2.insert(s2[i]-'A'+1,i,s2);
	for(int i=t1.cnt;i;i--) t1.val[t1.nxt[i]]+=t1.val[i];
	for(int i=t2.cnt;i;i--) t2.val[t2.nxt[i]]+=t2.val[i];
	dfs(t1.root0,t2.root0);
	dfs(t1.root1,t2.root1);
	printf("%lld\n",ans);
	return 0;
}
