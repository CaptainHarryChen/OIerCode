#include<cstdio>
#define MAXN 1005
int N,K,A[MAXN],B[MAXN];
bool vis[MAXN];
int main()
{
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",&B[i]);
	for(int i=1,j;i<=N;i++)
	{
		for(j=1;B[j]||vis[j];j++);
		A[i]=j;
		vis[j]=1;
		for(int k=j-K;k>0;k--)
			B[k]--;
	}
	for(int i=1;i<N;i++)
		printf("%d ",A[i]);
	printf("%d\n",A[N]);
	return 0;
}
