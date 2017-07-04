#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	char a,b;
	scanf("%c %c",&a,&b);
	if(a>b)swap(a,b);
	if((b-a)%2)printf("%c\n",b+1);
	else printf("%c\n",a-1);
	return 0;
}
