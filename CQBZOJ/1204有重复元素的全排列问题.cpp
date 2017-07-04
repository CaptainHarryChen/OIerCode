#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s[15],ss[15];
int n[26],len,cnt;
void f(int a)
{
    if(a>len)
    {
        cnt++;
        printf("%d:%s\n",cnt,ss);
    }
    for(int i=0;i<26;i++)
    {
        if(n[i]!=0)
        {
            ss[a-1]=i+'a';
            n[i]--;
            f(a+1);
            ss[a-1]=0;
            n[i]++;
        }
    }
}
int main()
{
	scanf("%s",s);
	len=strlen(s);
    for(int i=0;i<len;i++)
        n[s[i]-'a']++;
    f(1);
    return 0;
}
