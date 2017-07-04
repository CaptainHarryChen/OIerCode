#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	char s[15];
	int x,len;
	scanf("%s%d",s,&x);
	len=strlen(s);
	if(x>len)printf("0\n");
	else if(x<=0)printf("0\n");
	else printf("%c\n",s[len-x]);
	return 0;
}
