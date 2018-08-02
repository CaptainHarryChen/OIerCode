#include<cstdio>
const int MAXN=100005;

int n,x;
int A[MAXN];
bool vis[MAXN],vis2[MAXN];

int main()
{
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);
		if(vis[A[i]])
		{
			puts("0");
			return 0;
		}
		vis[A[i]]=true;
	}
	
	for(int i=1;i<=n;i++)
	{
		int y=A[i]&x;
		if(y!=A[i]&&vis[y])
		{
			puts("1");
			return 0;
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		if(vis2[A[i]&x])
		{
			puts("2");
			return 0;
		}
		vis2[A[i]&x]=true;
	}
	
	puts("-1");
	
	return 0;
}
