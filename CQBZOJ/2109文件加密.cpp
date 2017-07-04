#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[1000];
int main()
{
	gets(s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		if(s[i]>='A'&&s[i]<='Z')
			s[i]=(s[i]-'A'+1+3)%26+'A'-1;
		else if(s[i]>='a'&&s[i]<='z')
			s[i]=(s[i]-'a'+1+3)%26+'a'-1;
		if(s[i]==96)s[i]='z';
		else if(s[i]==64)s[i]='Z';
	}
	puts(s);
}
