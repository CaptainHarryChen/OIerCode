#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char s[50];
using namespace std;
int main()
{
	int m=0,len,i;
	for(i=0;scanf("%s",s)==1;i++)
	{
		len=strlen(s);
		m+=len;
	}
	printf("%.1lf\n",(double)m/i);
	return 0;
}
