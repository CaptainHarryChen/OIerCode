#include<cstdio>
#include<cstring>
#define SIZE 450
#define ZERO 220
#define MAXN 22
const int dd[4][2]={{1,0},{0,1},{0,-1},{-1,0}};
const char str_d[5]="ensw";
int T,n,m,path[MAXN],cnt;
bool vis[SIZE][SIZE],p[SIZE][SIZE];
bool check(int x,int y,int d,int s)
{
	for(int i=1;i<=s;i++)
	{
		x+=dd[d][0],y+=dd[d][1];
		if(p[x][y])
			return 0;
	}
	return 1;
}
void dfs(int a,int b,int k)
{
	if(k>=n)
	{
		if(a==ZERO&&b==ZERO)
		{
			for(int i=0;i<k;i++)
				printf("%c",str_d[path[i]]);
			printf("\n");
			cnt++;
		}
		return;
	}
	for(int i=0;i<4;i++)
	{
		if((path[k-1]==0||path[k-1]==3)&&(i==0||i==3))continue;
		if((path[k-1]==1||path[k-1]==2)&&(i==1||i==2))continue;
		if(check(a,b,i,k+1))
		{
			if(vis[a+dd[i][0]*(k+1)][b+dd[i][1]*(k+1)])continue;
			vis[a+dd[i][0]*(k+1)][b+dd[i][1]*(k+1)]=1;
			path[k]=i;
			dfs(a+dd[i][0]*(k+1),b+dd[i][1]*(k+1),k+1);
			vis[a+dd[i][0]*(k+1)][b+dd[i][1]*(k+1)]=0;
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		memset(vis,0,sizeof vis);
		memset(p,0,sizeof p);
		for(int i=1,a,b;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			p[a+ZERO][b+ZERO]=1;
		}
		cnt=0;
		for(int i=0;i<4;i++)
			if(!p[dd[i][0]+ZERO][dd[i][1]+ZERO])
			{
				vis[dd[i][0]+ZERO][dd[i][1]+ZERO]=1;
				path[0]=i;
				dfs(dd[i][0]+ZERO,dd[i][1]+ZERO,1);
				vis[dd[i][0]+ZERO][dd[i][1]+ZERO]=0;
			}
		printf("Found %d golygon(s).\n\n",cnt);
	}
	return 0;
}
