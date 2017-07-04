#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char arr[20][20],s[20][20],arr2[20][20];
int n;
void fangfa1()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			s[i][j]=arr[n-j-1][i];
}
void fangfa2()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			s[i][j]=arr[n-i-1][n-j-1];
}
void fangfa3()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			s[i][j]=arr[j][n-i-1];
}
void fangfa4()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			s[i][j]=arr[i][n-j-1];
}
void debug()
{
	puts("");
	for(int i=0;i<n;i++)
		puts(s[i]);
	puts("");
}
bool check()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(s[i][j]!=arr2[i][j])
				return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%s",arr[i]);
	for(int i=0;i<n;i++)
		scanf("%s",arr2[i]);
	fangfa1();
	//debug();
	if(check())
	{printf("1\n");return 0;}
	fangfa2();
	//debug();
	if(check())
	{printf("2\n");return 0;}
	fangfa3();
	//debug();
	if(check())
	{printf("3\n");return 0;}
	fangfa4();
	if(check())
	{printf("4\n");return 0;}
	memcpy(s,arr,sizeof arr);
	if(check())
	{printf("6\n");return 0;}
	fangfa4();
	memcpy(arr,s,sizeof s);
	fangfa1();
	if(check())
	{printf("5\n");return 0;}
	fangfa2();
	if(check())
	{printf("5\n");return 0;}
	fangfa3();
	if(check())
	{printf("5\n");return 0;}
	printf("7\n");
	return 0;
}
