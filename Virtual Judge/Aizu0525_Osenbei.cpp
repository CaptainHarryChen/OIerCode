#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXR 12
#define MAXC 10005
int R,C;
int map[MAXR][MAXC];
int op[MAXR];
int main()
{
	while(1)
	{
		scanf("%d%d",&R,&C);
		if(R==0&&C==0)
			break;
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				scanf("%d",&map[i][j]);
		int ans=0;
		for(int op=0;op<(1<<R);op++)
		{
			int sum=0;
			for(int j=1,s;j<=C;j++)
			{
				s=0;
				for(int i=1;i<=R;i++)
					if(op&(1<<(i-1)))
						s+=map[i][j]^1;
					else
						s+=map[i][j];
				if(s<=R/2)
					s=R-s;
				sum+=s;
			}
			ans=max(ans,sum);
		}
		printf("%d\n",ans);
	}
	return 0;
}
