#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s[1005];
using namespace std;
int main()
{
	gets(s);
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		if(s[i]=='z')
			s[i]='a';
		else if(s[i]=='Z')
			s[i]='A';
		else if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
			s[i]++;
	}
	printf("%s\n",s);
	return 0;
}
