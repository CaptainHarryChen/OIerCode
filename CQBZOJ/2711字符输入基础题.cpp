#include<cstdio>
#include<iostream>
using namespace std;
char s[1000][1000];
int main()
{
	char ss[4];
	gets(ss);
	int n=ss[0]-'0';
	for(int i=0;i<n;i++)
		gets(s[i]);
	for(int i=0;i<n;i++)
		printf("%s\n",s[i]);
	return 0;
}
