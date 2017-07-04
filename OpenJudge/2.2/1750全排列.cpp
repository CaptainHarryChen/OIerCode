#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n;
char num[25],s[25];
bool f[25];
void dfs(int k)
{
	if(k==n)
	{
		puts(num);
	}
	for(int i=0;i<n;i++)
	{
		if(f[i])continue;
		num[k]=s[i];
		f[i]=1;
		dfs(k+1);
		f[i]=0;
		num[k]=0;
	}
}
int main()
{
	scanf("%s",s);
	n=strlen(s);
	dfs(0);
	return 0;
}
