#include<cstdio>
#include<cstdlib>
long long n,sum,num[7000],t[7000];
void dfs(long long k,long long s,long long cur)
{
	if(!s)
	{
		for(long long i=1;i<cur;i++)
			printf("%I64d ",t[i]);
		printf("\n");
		exit(0);
	}
	if(s<0)return;
	if(cur>n)
	{
		printf("No Solution!\n");
		exit(0);
	}
	if(k>n)return;
	t[cur]=num[k];
	dfs(k+1,s-num[k],cur+1);
	dfs(k+1,s,cur);
}
int main()
{
	scanf("%I64d%I64d",&n,&sum);
	for(long long i=1;i<=n;i++)
		scanf("%I64d",&num[i]);
	dfs(1,sum,1);
	printf("No Solution!\n");
	return 0;
}
