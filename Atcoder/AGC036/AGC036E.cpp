#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
int a[N],b[N],n;
int c[3];char ch[4];
void read()
{
    int c=0;
    while((c=getchar())!='\n')
    if(!n || a[n]!=c-'A') a[++n]=c-'A';
}
int main()
{
    read();
    a[0]=b[0]=4;
    for(int i=1;i<=n;i++) c[a[i]]++;
    ch[0]='A',ch[1]='B',ch[2]='C';
    for(int i=0;i<2;i++)
        for(int j=0;j<=1;j++) if(c[j]>c[j+1]) swap(c[j],c[j+1]),swap(ch[j],ch[j+1]);
    for(int i=1;i<=n;i++)
        for(int j=0;j<=2;j++) if(a[i]==ch[j]-'A'){a[i]=j;break;}
    int m=0;
    for(int i=1;i<=n;i++)
    if(c[2]>c[1] && i!=n && a[i]==2 && (a[i-1]!=a[i+1] || !m)) --c[2];
    else b[++m]=a[i];
    if(c[2]>c[1] && b[m]==2) c[2]--,m--;
    n=0;
    for(int i=1;i<=m;i++)
    if(c[2]>c[1] && i!=m && (b[i]^b[i+1])==2) --c[2],--c[0],++i;
    else a[++n]=b[i];
    m=0;
    for(int i=1;i<=n;i++)
    if(c[1]>c[0] && i!=n && (a[i]^a[i+1])==3 && a[i-1]!=0) --c[1],++i;
    else b[++m]=a[i];
    for(int i=1;i<=m;i++) putchar(ch[b[i]]);
    return 0;
}