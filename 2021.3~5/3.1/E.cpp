#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define N 100010
using namespace std;
int f[N],s[N],c[N],n;
int find(int x){return x==f[x]?f[x]:(f[x]=find(f[x]));}
bool merge(int x,int y)
{
    if(!f[x] || !f[y]) return false;
    x=find(x),y=find(y);
    if(x==y) return false;
    c[s[x]]--;c[s[y]]--;
    f[x]=y,s[y]+=s[x];
    c[s[y]]++;
    return true;
}
int a[N],t[N];
int cmp(int x,int y){return a[x]<a[y];}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),t[i]=i;
    sort(t+1,t+n+1,cmp);
    int b=0,mx=0,res=0;
    for(int l=1,r=1;l<=n;l=r)
    {
        for(r=l;r<=n && a[t[r]]==a[t[l]];r++)
        {
            int u=t[r];b++;
            c[s[u]=1]++;f[u]=u;
            b-=merge(u-1,u),b-=merge(u,u+1);
        }
        if(b==c[s[find(t[l])]] && b>mx) mx=b,res=a[t[l]]+1;
    }
    printf("%d\n",res);
    return 0;
}