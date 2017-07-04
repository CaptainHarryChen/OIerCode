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
		if(s[i]>='A'&&s[i]<='Z')
			s[i]+=32;
	for(int i=0;i<len;i++)
		if(s[i]>='a'&&s[i]<='z')
			z[s[i]-97]++;
	for(int i=0;i<26;i++)
		for(int j=1;j<=z[i];j++)
			printf("%c",i+97);
	cout<<endl;
	return 0;
}
