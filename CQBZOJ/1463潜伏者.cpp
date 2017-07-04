#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 105
char a[MAXN],b[MAXN],c[MAXN],key[30],key2[30];
int n;
int main()
{
	scanf("%s%s%s",a,b,c);
	n=strlen(a);
	bool flag=1;
	for(int i=0;i<n;i++)
		if(key[a[i]-'A']&&b[i]!=key[a[i]-'A'])
		{flag=0;break;}
		else if(!key[a[i]-'A'])
			key[a[i]-'A']=b[i];
	for(int i=0;i<n;i++)
		if(key2[b[i]-'A']&&a[i]!=key2[b[i]-'A'])
		{flag=0;break;}
		else if(!key2[b[i]-'A'])
			key2[b[i]-'A']=a[i];
	for(int i=0;i<26;i++)
		if(!key[i])
		{flag=0;break;}
	if(flag)
	{
		int len=strlen(c);
		for(int i=0;i<len;i++)
			c[i]=key[c[i]-'A'];
		printf("%s\n",c);
	}
	else
		printf("Failed\n");
	return 0;
}
