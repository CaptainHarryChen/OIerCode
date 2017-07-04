#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 2005
int N,M;
int fla[MAXN];
int cus[MAXN][MAXN*2];
int main()
{
	int C;
	scanf("%d",&C);
	for(int Case=1;Case<=C;Case++)
	{
		scanf("%d%d",&N,&M);
		memset(fla,0,sizeof fla);
		for(int i=1;i<=M;i++)
		{
			scanf("%d",&cus[i][0]);
			for(int j=1;j<=2*cus[i][0];j+=2)
				scanf("%d%d",&cus[i][j],&cus[i][j+1]);
		}
		int suc=-1;
		while(suc==-1)
		{
			bool nounsut=1;
			for(int i=1;i<=M;i++)
			{
				bool sut=0,unm=1;
				for(int j=1;j<=2*cus[i][0];j+=2)
				{
					if(cus[i][j+1]==1)
						unm=0;
					if(fla[cus[i][j]]==cus[i][j+1])
					{
						sut=1;
						break;
					}
				}
				if(!sut)
				{
					nounsut=0;
					if(unm)
						suc=0;
					else
						for(int j=1;j<=2*cus[i][0];j+=2)
							if(cus[i][j+1]==1)
							{
								fla[cus[i][j]]=1;
								break;
							}
				}
			}
			if(nounsut)
				suc=1;
		}
		if(suc==0)
			printf("Case #%d: IMPOSSIBLE\n",Case);
		else
		{
			printf("Case #%d:",Case);
			for(int i=1;i<=N;i++)
				printf(" %d",fla[i]);
			puts("");
		}
	}
	return 0;
}
