#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	char c;
	while(scanf("%c",&c)==1)
	{
		if(c>='a'&&c<='z')
			c-=32;
		else if(c>='A'&&c<='Z')
			c+=32;
		printf("%c",c);
	}
	return 0;
}
