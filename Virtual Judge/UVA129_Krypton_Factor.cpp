#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,l,cnt;
char s[5010];
bool f;
bool check(int m)
{
	bool ff=0;
	for(int i=1;i*2<=m+1;i++)
	{
		ff=0;
		for(int j=0;j<i;j++)
			if(s[m-i-j]!=s[m-j])
			{ff=1;break;}
		if(!ff)return 0;
	}
	return 1;
}
void dfs(int k)
{
	
	if(cnt==n)
	{
		int tot=0;
		for(int j=0;j<k-1;j++)
		{
			printf("%c",s[j]);
			if((j+1)%4==0)
			{
				tot++;
				if(tot!=16)
					printf(" ");
				else 
					printf("\n");
			}
		}
		printf("%c\n%d\n",s[k-1],k);
		f=1;return;
	}
	cnt++;
	for(int i=0;i<l;i++)
	{
		s[k]=i+'A';
		if(!check(k))continue;
		dfs(k+1);
		if(f)return;
	}
}
int main()
{
	while(~scanf("%d%d",&n,&l))
	{
		if(!n&&!l)return 0;
		f=0;
		cnt=0;
		dfs(0);
	}
	return 0;
}
