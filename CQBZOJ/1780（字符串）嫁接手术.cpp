#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s1[105],s2[105],s[210];
using namespace std;
int main()
{
	gets(s1);
	gets(s2);
	int f=1;
	for(int i=0;s1[i]||s2[i];i++)
		if(s1[i]<s2[i])
			f=0;
	if(f==1)
	{
		strcpy(s,s1);
		strcat(s,s2);
	}
	else
	{
		strcpy(s,s2);
		strcat(s,s1);
	}
	puts(s);
	return 0;
}
