#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define N 100010
using namespace std;
string a1("F.exe"),a2("F-.exe"),a3("randF.exe");
string t1("A.in"),t2("F.out"),t3("F-.out"),err("Err.txt");
//string ex("rand.txt");
int main()
{
    int T=100;
    for(int i=1;i<=T;i++)
    {
        system((a3+/*"<"+ex+*/">"+t1).c_str());
        system((a1+"<"+t1+">"+t2).c_str());
        system((a2+"<"+t1+">"+t3).c_str());
        if(system((string("fc ")+t2+" "+t3+">"+err).c_str())){printf("WA on test %3d\n",i);return 1;}
        // _sleep(100);
        printf("Accepted on test %3d\n",i);
    }
    return 0;
}