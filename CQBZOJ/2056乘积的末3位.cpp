#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
char s[1000];
int a[100];
int main()
{
	gets(s);
	int len=strlen(s),k,n,x=0;
	for(int i=len-1,j,m=0;i>=0;i--)
		if((s[i]>='0'&&s[i]<='9'))
		{
			for(j=i,k=1,m=0;(s[j]>='0'&&s[j]<='9')||(s[j]=='-'&&(s[j+1]>='0'&&s[j+1]<='9'));j--,k++)
			{
				if(s[j]=='-'&&(s[j+1]>='0'&&s[j+1]<='9')){m=0-m;break;}
				n=1;
				for(int l=1;l<k;l++)
					n*=10;
				m+=((s[j]-'0')*n)%1000;
				i=j;
			}
			a[x++]=m;
		}
	k=1;
	for(int i=0;i<x;i++)
	{
		k*=a[i];
		k%=1000;
	}
	if(k<0)
	{
		k=(0-k)%1000;
		printf("%03d\n",0-k);
	}
	else
	{
		k%=1000;
		printf("%03d\n",k);
	}
	return 0;
}
