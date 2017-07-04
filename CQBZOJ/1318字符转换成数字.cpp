#include<cstdio>
#include<iostream>
#include<cstring>
#define INF 2139062143
using namespace std;
int main()
{
	char a;
	scanf("%c",&a);
	if(a>='a'&&a<='d')
		printf("%d\n",(int)a-'a'+1);
	else if(a>='A'&&a<='D')
		printf("%d\n",(int)a-'A'+1);
	else
		printf("5\n");
	return 0;
}
