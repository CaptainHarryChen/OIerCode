#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 105
int N,P,Q;
struct WAR
{
	int s,t;
}war[MAXN];
bool cmp(WAR a,WAR b)
{return a.s<b.s||(a.s==b.s&&a.t<b.t);}
char str[MAXN];
int main()
{
	while(~scanf("%d",&N))
	{
		scanf("%d%d",&P,&Q);
		for(int i=1;i<=N;i++)
		{
			scanf("%d%d",&war[i].s,&war[i].t);
			gets(str);
		}
		sort(war+1,war+N+1,cmp);
		bool flag=0;
		int ans=Q;
		for(int i=1;i<=N;i++)
			if(war[i].s<=ans&&war[i].t>=ans)
				ans=war[i].s-1;
			else
			{
				printf("%d\n",ans);
				flag=1;
				break;
			}
		if(!flag)
			printf("Badly!\n");
	}
	return 0;
}
