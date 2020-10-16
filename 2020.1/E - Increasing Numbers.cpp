#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
using namespace std;
int num[N],tot;
void mul(int num[],int &len,int k)
{
	int up=0;
	tot=0;
	for(int i=1;i<=len;i++){
		up=num[i]*k+up;
		num[i]=up%10;
		tot+=num[i];
		up/=10;
	}
	if(up) num[++len]=up;
	tot+=up;
}
void add(int num[],int &len,int k)
{
	tot-=num[1];
	num[1]+=k;
	int up=num[1]/10;
	num[1]%=10;
	tot+=num[1];
	for(int i=2;i<=len;i++){
		tot-=num[i];
		num[i]+=up;
		up=num[i]/10;
		num[i]%=10;
		tot+=num[i];
		if(!up)break;
	}
	if(up) num[++len]=up;
	tot+=up;
}
int main()
{
	int n=0,ch;
	while((ch=getchar())!=EOF) num[++n]=ch-'0';
	reverse(num+1,num+n+1);
	mul(num,n,9);
	for(int i=1;i<=n;i++)
	{
		add(num,n,9);
		if(tot%9==0 && i*9>=tot)
		{
			printf("%d",i);
			break;
		}
	}
	return 0;
}

