#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=53,MAXS=105;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int n,m;
char mp[MAXN][MAXN];
char s[MAXS];
int order[4]={0,1,2,3};
int sx,sy;

bool check()
{
	int x=sx,y=sy;
	for(int i=0;s[i];i++)
	{
		x+=dir[order[s[i]-'0']][0],y+=dir[order[s[i]-'0']][1];
		if(x<=0||y<=0||x>n||y>m||mp[x][y]=='#')
			return false;
		if(mp[x][y]=='E')
			return true;
	}
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='S')
				sx=i,sy=j;
	}
	scanf("%s",s);
	int ans=0;
	do
	{
		ans+=check();
	}while(next_permutation(order,order+4));
	printf("%d\n",ans);
	return 0;
}
