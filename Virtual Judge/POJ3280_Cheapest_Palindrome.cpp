#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,cost[30],f[2015][2015];
char s[2015];
int main()
{
	memset(f,100,sizeof(f));
	scanf("%d%d%s",&n,&m,s+1);
	char c;
	int a,b;
	for(int i=0;i<n;i++)
	{
		scanf("%c%c%d%d",&c,&c,&a,&b);
		cost[c-'a']=min(a,b);
	}
	for(int x=m;x>0;x--)
		for(int y=x;y<=m;y++)
		{
			if(x==y||(y-x==1&&s[x]==s[y]))
				f[x][y]=0;
			else if(s[x]==s[y])
				f[x][y]=min(f[x][y],f[x+1][y-1]);
			else
			{
				f[x][y]=min(f[x][y],f[x+1][y]+cost[s[x]-'a']);
				f[x][y]=min(f[x][y],f[x][y-1]+cost[s[y]-'a']);
			}
		}
	printf("%d\n",f[1][m]);
	return 0;
}