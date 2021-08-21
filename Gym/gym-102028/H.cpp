#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#define N 200010
using namespace std;
typedef long long ll;
map<int,int>ch[N<<1];
int las=1,cnt=1,fa[N<<1],len[N<<1];
int insert(int c)
{
    int p=las,q=las=++cnt;
    len[q]=len[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=q;
    if(!p) fa[q]=1;
    else
    {
        int np=ch[p][c];
        if(len[np]==len[p]+1) fa[q]=np;
        else
        {
            int nq=++cnt;
            len[nq]=len[p]+1;fa[nq]=fa[np];
            ch[nq]=ch[np];fa[q]=fa[np]=nq;
            for(;p && ch[p][c]==np;p=fa[p]) ch[p][c]=nq;
        }
    }
    return q;
}
int a[N];
ll s[N];int ton[N],tp;
void clear(){tp=0;for(int i=1;i<=cnt;i++) fa[i]=len[i]=0,ch[i].clear();cnt=las=1;}
int main()
{
    int t;
    scanf("%d",&t);
    while(t --> 0)
    {
        int n;
        scanf("%d",&n);
        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            int u=insert(a[i]),v=len[u]-len[fa[u]];
            while(tp && a[ton[tp]]<=a[i]) tp--;
            ton[++tp]=i;s[tp]=s[tp-1]+1ll*a[i]*(i-ton[tp-1]);
            int p=lower_bound(ton+1,ton+tp+1,v)-ton;
            ans+=s[p]-1ll*a[ton[p]]*(ton[p]-v);
        }
        printf("%lld\n",ans);
        clear();
    }
    return 0;
}