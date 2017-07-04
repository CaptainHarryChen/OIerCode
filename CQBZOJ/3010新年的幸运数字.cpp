#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 1010
using namespace std;
char op[12][5];
int N,num[12],print[MAXN],cnt;
bool check(int a)
{
	long long x=a;
	for(int i=1;i<=N;i++)
	{
		switch(op[i][0])
		{
			case 'A':x+=num[i];break;
			case 'S':x-=num[i];break;
			case 'D':x/=num[i];break;
			case 'M':
				if(op[i][1]=='U')
				{x*=num[i];break;}
				else
				{x%=num[i];break;}
		}
	}
	char s[25]={0};
	sprintf(s,"%lld",x);
	for(int i=0;s[i];i++)
		if(s[i]!='4'&&s[i]!='7'&&s[i]!='-')
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%s%d",op[i],&num[i]);
	for(int i=1;i<=1000;i++)
		if(check(i))
			print[++cnt]=i;
	if(cnt==0)
	{printf("bad luck\n");return 0;}
	printf("%d\n",cnt);
	for(int i=1;i<cnt;i++)
		printf("%d ",print[i]);
	printf("%d\n",print[cnt]);
	return 0;
}
