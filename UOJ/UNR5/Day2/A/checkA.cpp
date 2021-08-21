#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<cassert>
#define N 1000010
using namespace std;
int op[N],x[N],y[N],id[N],fl[N];
int s[N],st;
int main()
{
    ifstream inp("A.in"),oup("A.out");
    int n,m;
    inp>>n>>m;
    for(int i=1;i<=n;i++)
    {
        inp>>op[i]>>x[i];
        if(op[i]==2) inp>>y[i];
    }
    for(int i=1;i<=n;i++) oup>>id[i];
    for(int i=1;i<=n;i++) oup>>fl[i];
    // for(int i=1;i<=n;i++) printf("%d ",fl[i]);puts("");
    for(int i=1;i<=n;i++)
    {
        if(op[id[i]]==1) s[++st]=x[id[i]];
        else
        {
            s[++st]=x[id[i]];s[++st]=y[id[i]];
            if(fl[i]) swap(s[st],s[st-1]);
            // printf("%d:%d %d %d\n",id[i],fl[id[i]],s[st-1],s[st]);
        }
    }
    for(int i=1;i*2<=st;i++) if(s[i]!=s[st-i+1])
    {
        for(int j=i;j<=st-i+1;j++) printf("%d ",s[j]);puts("");printf("Wrong on %d\n",i);
        system("pause");
        return 0;
    }
    for(int j=1;j<=st;j++) printf("%d ",s[j]);puts("");
    puts("Right");
    return 0;
}