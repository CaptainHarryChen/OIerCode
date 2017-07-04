#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
char C[40];
bool check(int &x)
{
	sprintf(C,"%d",x);
	int len=strlen(C);
	if(len%2==0&&x!=11)
	{x=pow(10,len)-1;return 0;}
	if(((C[0]-'0')%2==0||(C[0]-'0')%5==0)&&len!=1)
	{
		x+=pow(10,len-1);x-=2;
		return 0;
	}
	for(int i=0,j=len-1;i<j;i++,j--)
		if(C[i]!=C[j])
			return 0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	for(int i=a%2==0?a+1:a;i<=b;i+=2)
		if(check(i))
			printf("%d\n",i);
	return 0;
}
