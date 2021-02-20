#include<iostream>
#include<cstdio>
#include<cstring>
#define N 500010
using namespace std;
char str[N];
struct PAM{
	int len[N],nxt[N],ch[N][30],val[N],cnt;
	int root0,root1,last;
	PAM(void)
	{
		root0=cnt++;
		last=root1=cnt++;
		len[root0]=0,nxt[root0]=root1;
		len[root1]=-1,nxt[root1]=root1;
	}
	void insert(int c,int l)
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
			val[q]=val[nxt[q]]+1;
		}
		last=ch[p][c];
	}
}t;

int main()
{
	scanf("%s",str);
	int len=strlen(str);
	for(int i=0;i<len;i++)
	{
		t.insert(str[i]-'a'+1,i);
		str[i+1]=(str[i+1]-97+t.val[t.last])%26+97;
		printf("%d ",t.val[t.last]);
	}
	return 0;
}

