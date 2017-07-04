#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int B;
char S[40];
void radix(int x,char s[])
{
	memset(s,0,sizeof s);
	int i;
	for(i=0;x!=0;i++)
	{
		s[i]=x%B+'0';
		x/=B;
	}
}
bool check(int x)
{
	radix(x,S);
	int len=strlen(S);
	for(int i=0,j=len-1;i<j;i++,j--)
		if(S[i]!=S[j])
			return 0;
	return 1;
}
void print(char s[])
{
	int len=strlen(s);
	for(int j=len-1;j>=0;j--)
	{
		if(s[j]>'9')
			printf("%c",s[j]-'9'-1+'A');
		else
			printf("%c",s[j]);
	}
}
int main()
{
	scanf("%d",&B);
	for(int i=1;i<=300;i++)
		if(check(i*i))
		{
			char ss[10]={0};
			radix(i,ss);
			print(ss);
			printf(" ");
			print(S);
			printf("\n");
		}
	return 0;
}
