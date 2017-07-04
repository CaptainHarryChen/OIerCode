#include<cstdio>
#include<cstring>
#define MAXN 10
const int ff[MAXN][MAXN]=
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,2,2,2,3,3,3},
	{0,1,1,1,2,2,2,3,3,3},
	{0,1,1,1,2,2,2,3,3,3},
	{0,4,4,4,5,5,5,6,6,6},
	{0,4,4,4,5,5,5,6,6,6},
	{0,4,4,4,5,5,5,6,6,6},
	{0,7,7,7,8,8,8,9,9,9},
	{0,7,7,7,8,8,8,9,9,9},
	{0,7,7,7,8,8,8,9,9,9}
};
int T,map[MAXN][MAXN],ans[MAXN][MAXN];
bool col[MAXN][MAXN],line[MAXN][MAXN],arr[MAXN][MAXN];
bool dfs(int a,int b)
{
	if(a>9)
		return 1;
	if(map[a][b]!=0)
	{if(dfs(a+(b==9),b==9?1:b+1))return 1;return 0;}
	for(int i=1;i<=9;i++)
		if(!col[b][i]&&!line[a][i]&&!arr[ff[a][b]][i])
		{
			col[b][i]=line[a][i]=arr[ff[a][b]][i]=1;
			ans[a][b]=i;
			if(dfs(a+(b==9),b==9?1:b+1))return  1;
			col[b][i]=line[a][i]=arr[ff[a][b]][i]=0;
		}
	return 0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(col,0,sizeof col);
		memset(line,0,sizeof line);
		memset(arr,0,sizeof arr);
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
			{
				scanf("%1d",&map[i][j]);
				if(!map[i][j])continue;
				col[j][map[i][j]]=1;
				line[i][map[i][j]]=1;
				arr[ff[i][j]][map[i][j]]=1;
			}
		memcpy(ans,map,sizeof map);
		dfs(1,1);
		for(int i=1;i<=9;i++)
		{
			for(int j=1;j<=9;j++)
				printf("%d",ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
