### [链接](https://www.luogu.com.cn/problem/CF914F)
多次求出现次数？那多半是SAM了。

还有修改？好像SAM不支持修改啊。可SAM是线性的，修改我们直接块外暴力，块内重构。询问大串暴力，小串预处理。

但好难写啊。。。这题居然开了4s，直接bitset套就好了。

考虑对每一个字符，暴力处理能匹配的位置，然后将所有字符与起来，统计 $l$ 到 $r$ 之间1的个数即可。

复杂度 $O(\frac{n^2}\omega)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#define N 100010
using namespace std;
bitset<N>b[27],r;
char s[N],t[N];
int main()
{
    scanf("%s",s+1);
    int n=strlen(s+1),m;
    for(int i=1;i<=n;i++)
    b[s[i]-'a'].set(i,1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int opt,x,y;
        scanf("%d%d",&opt,&x);
        if(opt==2)
        {
            scanf("%d%s",&y,t);
            int k=strlen(t),res=0;
            r.set();
            for(int j=0;j<k;j++) r&=b[t[j]-'a']>>j;
            int lf=(r>>x).count(),rf=(r>>(y-k+2)).count();
            if(lf<rf) lf=rf;
            printf("%d\n",lf-rf);
        }
        else
        {
            char c[2];
            scanf("%s",c);
            b[s[x]-'a'].set(x,0);
            s[x]=c[0];
            b[s[x]-'a'].set(x,1);
        }
    }
    return 0;
}
```
