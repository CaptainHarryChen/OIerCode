#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int dd[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int n,m,cnt[105][105];
char s[105][105];
bool check(int x,int y)
{
	if(x<=0||x>n||y<=0||y>m||s[x][y]=='*')
		return 0;
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='*')
				for(int k=0,ii,jj;k<8;k++)
				{
					ii=i+dd[k][0];jj=j+dd[k][1];
					if(!check(ii,jj))continue;
						cnt[ii][jj]++;
				}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='*')
				printf("*");
			else
				printf("%d",cnt[i][j]);
		}
		printf("\n");
	}
	return 0;
}
