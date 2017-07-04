#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 1000
using namespace std;
char s[MAXN];
int n,r[MAXN],l[MAXN];
int main()
{
	scanf("%d%s",&n,s+1);
	strncpy(s+n+1,s+1,n);
	for(int i=1;i<=n;)
	{
		int j,x=1000;
		for(j=i+1;(s[j]==s[i]||s[j]=='w')&&j!=i+n;j++)
			if(s[j]=='w'&&x>j)x=j;
		if(s[i]=='w')
		{
			int y=j;
			for(j++;(s[j]==s[y]||s[j]=='w')&&j!=i+n;j++)
				if(s[j]=='w'&&x>j)x=j;
		}
		for(int k=j-1;k>=i;k--)
			r[k]=j-k;
		i=x;
		if(i==1000)i=j;
	}
	r[n+1]=r[1];
	for(int i=n*2;i>n;)
	{
		int j,x=0;
		for(j=i-1;(s[j]==s[i]||s[j]=='w')&&j!=i-n;j--)
			if(s[j]=='w'&&x<j)x=j;
		if(s[i]=='w')
		{
			int y=j;
			for(j--;(s[j]==s[y]||s[j]=='w')&&j!=i-n;j--)
				if(s[j]=='w'&&x<j)x=j;
		}
		for(int k=j+1;k<=i;k++)
			l[k-n]=k-j;
		i=x;
		if(i==0)i=j;
	}
	int maxs=0,sum;
	for(int i=1;i<=n;i++)
	{
		sum=l[i]+r[i+1];
		maxs=max(maxs,sum);
	}
	printf("%d\n",min(maxs,n));
	return 0;
}
