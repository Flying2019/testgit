#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
using namespace std;
char s[N];
int ch[N][3],val[N],cnt;bool tag[N];
void build(int &u,int d,int p=0,int l=1)
{
    u=++cnt;
    if(!d){val[u]=p;return;}
    for(int i=0;i<2;i++) build(ch[u][i],d-1,p+i*l,l*3);
}
void set_tag(int u){tag[u]^=1;swap(ch[u][1],ch[u][2]);}
void push_down(int u)
{
    if(!tag[u]) return;
    for(int i=0;i<2;i++) set_tag(ch[u][i]);
    tag[u]=false;
}
int main()
{
    int n;
    scanf("%d",&n);
    return 0;
}