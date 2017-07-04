#include<cstdio>
#define MAXN 100005
int Set[MAXN];
bool rel[MAXN];
int Root(int x)
{
	if(Set[x]==x)
		return x;
	int t=Root(Set[x]);
	rel[x]=rel[x]^rel[Set[x]];
	return Set[x]=t;
}
int main()
{
	int T,N,M,a,b;
	char op[2];
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
			Set[i]=i,rel[i]=0;
		if(N==2)
		{Set[1]=2,rel[1]=1;}
		for(int i=1;i<=M;i++)
		{
			scanf("%s%d%d",op,&a,&b);
			if(op[0]=='A')
			{
				int r1=Root(a),r2=Root(b);
				if(r1!=r2)
				{
					printf("Not sure yet.\n");
					continue;
				}
				if(rel[a]^rel[b])
					printf("In different gangs.\n");
				else
					printf("In the same gang.\n");
			}
			else
			{
				int r1=Root(a),r2=Root(b);
				Set[r1]=r2;
				rel[r1]=rel[a]^1^rel[b];
			}
		}
	}
	return 0;
}
