#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
string s,t;
int main()
{
    int _;
    scanf("%d",&_);
    while(_ --> 0)
    {
        cin>>s>>t;
        for(int i=0;i<s.size();i++)
        {
            int d=0;
            if(s[i]==t[d])
            {
                int j=i;
                while(s[j]==t[d] && j<s.size())
                {
                    j++;d++;
                    if(d==t.size()){puts("YEs");return 0;}
                }
                j--;
                while(s[j-1]==t[d] && j>0)
                {
                    j--;d++;
                    if(d==t.size()){puts("YEs");return 0;}
                }
            }
        }
        puts("NO");
    }
    return 0;
}