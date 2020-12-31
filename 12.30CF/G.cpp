#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200010
#define M 2000010
#define mod 1000000007
using namespace std;
char s[N],st[N],t[M];
int nxt[M],_2[N];
void get_nxt(char s[])
{
    int n=strlen(s+1);
    int p=nxt[1]=0;
    for(int i=2;i<=n;i++)
    {
        while(p && s[i]!=s[p+1]) p=nxt[p];
        if(s[p+1]==s[i]) p++;
        nxt[i]=p;
    }
}
int pp(char s[],char t[])
{
    get_nxt(t);
    int n=strlen(s+1),m=strlen(t+1),p=0;
    int c=0;
    for(int i=1;i<=n;i++)
    {
        while(p && s[i]!=t[p+1]) p=nxt[p];
        if(t[p+1]==s[i]) p++;
        if(p==m){c++;p=nxt[p];}
    }
    return c;
}
char pre[M],suf[M];
char us[M<<1];
int slen,tlen,res[27];
int pre_work(char c)
{
    tlen=0;
    for(int i=1;i<=slen;i++) us[++tlen]=pre[i];
    us[++tlen]=c;
    for(int i=1;i<=slen;i++) us[++tlen]=suf[i];
    us[tlen+1]='\0';
    return pp(us,t);
}
int work(int p,int len)
{
    if(p==0)
    {
        memset(res,0,sizeof(res));
        slen=strlen(s+1);
        for(int i=1;i<=slen;i++) pre[i]=suf[i]=s[i];
        if(slen>=len-1)
        {
            for(int i=1;i<len;i++) suf[i]=s[i];suf[len]='\0';
            for(int i=1;i<len;i++) pre[i]=s[slen-len+i+1];pre[len]='\0';
            slen=len-1;
            for(char i='a';i<='z';i++) res[i-'a']=pre_work(i);
        }
        return 0;
    }
    int ans=work(p-1,len);
    ans=2ll*ans%mod;
    if(slen==len-1){ans=(ans+res[st[p]-'a'])%mod;return ans;}
    ans=(ans+pre_work(st[p]))%mod;
    if(tlen<len-1)
    {
        for(int i=1;i<=tlen;i++) suf[i]=us[i];suf[tlen+1]='\0';
        for(int i=1;i<=tlen;i++) pre[i]=us[i];pre[tlen+1]='\0';
        slen=tlen;
        return ans;
    }
    for(int i=1;i<len;i++) suf[i]=us[i];suf[len]='\0';
    for(int i=1;i<len;i++) pre[i]=us[tlen-len+i+1];pre[len]='\0';
    slen=len-1;
    for(char i='a';i<='z';i++) res[i-'a']=pre_work(i);
    return ans;
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    scanf("%s%s",s+1,st+1);
    _2[0]=1;
    for(int i=1;i<=N-10;i++) _2[i]=_2[i-1]*2ll%mod;
    while(q --> 0)
    {
        int p;
        scanf("%d%s",&p,t+1);
        int m=strlen(t+1);
        int ans=1ll*_2[p]*pp(s,t)%mod;
        printf("%d\n",(ans+work(p,m))%mod);
    }
    return 0;
}