#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
char a[10],b[10];
int main()
{
	scanf("%s%s",a,b);
	int sa=1,sb=1;
	int len1=strlen(a),len2=strlen(b);
	for(int i=0;i<len1;i++)
		sa*=a[i]-'A'+1;
	for(int i=0;i<len2;i++)
		sb*=b[i]-'A'+1;
	if(sa%47==sb%47)
		printf("GO");
	else
		printf("STAY");
	return 0;
}
