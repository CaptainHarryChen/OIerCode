#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s[1005];
int z[30];
using namespace std;
int main()
{
	gets(s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
		if(s[i]>='a'&&s[i]<='z')
			z[s[i]-97]++;
	for(int i=0;i<26;i++)
		printf("%c:%d\n",i+97,z[i]);
	return 0;
}
