#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 55
using namespace std;
int n,score[MAXN];
char s[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			switch(s[j])
			{
				case 'W':sum+=3;break;
				case 'D':sum+=1;score[j]+=1;break;
				case 'L':score[j]+=3;break;
			}
		score[i]+=sum;
	}
	int maxs=0;
	for(int i=1;i<=n;i++)
		maxs=max(maxs,score[i]);
	bool f=0;
	for(int i=1;i<=n;i++)
		if(score[i]==maxs)
		{
			if(!f)
			{printf("%d",i);f=1;}
			else printf(" %d",i);
		}
	printf("\n");
	return 0;
}
