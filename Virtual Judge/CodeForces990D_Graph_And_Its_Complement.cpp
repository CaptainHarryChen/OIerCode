#include<cstdio>
const int MAXN=1005;

int n,a,b;
bool adj[MAXN][MAXN];

int main()
{
	scanf("%d%d%d",&n,&a,&b);
	if((a>1&&b>1)||(a==1&&b==1&&n>1&&n<=3))
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	if(a==1)
	{
		for(int i=2;i<=n-b+1;i++)
			adj[i][i-1]=adj[i-1][i]=true;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				adj[i][j]^=1;
	}
	else if(b==1)
	{
		for(int i=2;i<=n-a+1;i++)
			adj[i][i-1]=adj[i-1][i]=true;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d",(i!=j)&&adj[i][j]);
		puts("");
	}
	
	return 0;
}
