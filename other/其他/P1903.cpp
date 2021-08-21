#include<iostream>
#include<cstdio>
#include<cstring>
#define N 150010
#define B 233
using namespace std;
int bl[N];
struct ques{
    int l,r,t;
    ques(int L=0,int R=0,int T=0):l(L),r(R),t(T){}
    bool operator <(const ques a)const
    {
        if(bl[l]!=bl[a.l]) return bl[l]<bl[a.l];
        if(bl[r]!=bl[a.r]) return bl[r]<bl[a.r];
        return t<a.t;
    }
}q[N];
struct modify{
    int p,c,r;
}mf[N];
int cm;
char op[2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%s%d%d",op,&x,&y);
        if(op[0]=='R')
        {
            ++cm;
            scanf("%d%d",&mf[cm].);
        }
    }
    return 0;
}