#include "worldline.h"
#include<iostream>
#include<cassert>
using namespace std;
const int N=10010;
int b[N],p[N];
int f0[N],s0[N],f1[N],s1[N],id[N];
int query_permutation(int n,int ans[])
{
    if(n==2) return 0;
    if(n==1){ans[1]=1;return 1;}
    int t=0;while(t*(t+1)/2<=n) b[t]=t*(t+1)/2,t++;
    b[t]=n;int rm=n-b[t-1];
    for(int i=1;i<=t;i++) cerr<<b[i]<<" ";cerr<<endl;
    new_round();
    for(int i=1;i<=n;i++) id[i]=0;
    for(int i=1;i<=t;i++)
        for(int j=b[i-1]+1;j<b[i];j++) id[j]=b[i];
    for(int i=1;i<=n;i++) addedge(i,id[i]),cerr<<id[i]<<" ";cerr<<endl;
    next_step();
    for(int i=1,c=0;i<=n;i++)
    {
        bool lnk=false;
        for(int j=1;j<=c;j++) if(query(i,p[j])){f0[i]=j;s0[j]++;lnk=true;break;}
        if(!lnk) p[f0[i]=++c]=i,s0[c]=1;
    }
    for(int i=1;i<=n;i++) cerr<<f0[i]<<" ";cerr<<endl;
    new_round();
    for(int i=1;i<=n;i++) id[i]=0;
    for(int i=n-rm+1;i<=n;i++) id[i]=b[i-n+t];
    for(int i=1;i<=t;i++)
        for(int j=i;j<t-1;j++) id[b[j]+i]=b[i];
    for(int i=1;i<=n;i++) addedge(i,id[i]),cerr<<id[i]<<" ";cerr<<endl;
    next_step();
    for(int i=1,c=0;i<=n;i++)
    {
        bool lnk=false;
        for(int j=1;j<=c;j++) if(query(i,p[j])){f1[i]=j;s1[j]++;lnk=true;break;}
        if(!lnk) p[f1[i]=++c]=i,s1[c]=1;
    }
    for(int i=1;i<=n;i++) cerr<<f1[i]<<" ";cerr<<endl;
    if(rm<t)
    {
        int x=1;
        for(;x<=n;x++) if(s0[f0[x]]==rm && s1[f1[x]]==1) break;
        for(int i=1;i<=n;i++) if(f0[x]==f0[i]) ans[n-s1[f1[i]]+1]=i,--s1[f1[i]];
        --t;s0[f0[x]]=0;
    }
    for(int i=1;i<=n;i++) if(s0[f0[i]]) ans[b[s0[f0[i]]-1]+t-s1[f1[i]]+1]=i;
    return 1;
}
