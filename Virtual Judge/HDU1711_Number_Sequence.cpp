#include<cstdio>
const int MAXN=1000005;

int n,m;
int A[MAXN],B[MAXN];
int fail[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		for(int i=1;i<=m;i++)
			scanf("%d",&B[i]);
		fail[0]=-1;
		for(int i=1;i<=m;i++)
		{
			int u=fail[i-1];
			while(u!=-1&&B[u+1]!=B[i])
				u=fail[u];
			fail[i]=u+1;
		}
		bool success=false;
		for(int i=1,j=0;i<=n;i++)
		{
			while(j&&A[i]!=B[j+1])
				j=fail[j];
			if(A[i]==B[j+1])
				j++;
			if(j==m)
			{
				printf("%d\n",i-j+1);
				success=true;
				break;
			}
		}
		if(!success)
			puts("-1");
	}
	return 0;
}
