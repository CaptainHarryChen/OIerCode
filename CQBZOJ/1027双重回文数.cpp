#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int N,S,B;
char C[40];
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
	memset(C,0,sizeof C);
	radix(x,C);
	int len=strlen(C);
	for(int i=0,j=len-1;i<j;i++,j--)
		if(C[i]!=C[j])
			return 0;
	return 1;
}
int main()
{
	scanf("%d%d",&N,&S);
	int cnt=0;
	for(int i=S+1;cnt<N;i++)
	{
		int j;
		for(B=2,j=0;B<=10;B++)
			if(check(i))
			{
				j++;
				if(j>=2)
				{
					cnt++;
					printf("%d\n",i);
					break;
				}
			}
	}
	return 0;
}
