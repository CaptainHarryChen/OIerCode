#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 23
int N,C;
struct coin
{
	int V,B;
}co[MAXN];
bool cmp(coin a,coin b)
{return a.V>b.V;}
int num[MAXN];
int main()
{
	scanf("%d%d",&N,&C);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&co[i].V,&co[i].B);
	sort(co+1,co+N+1,cmp);
	int ans=0;
	while(1)
	{
		int sum=0;
		for(int i=1;i<=N;i++)
		{
			num[i]=min(co[i].B,(C-sum)/co[i].V);
			sum+=co[i].V*num[i];
		}
		if(sum==C)
		{
			int mn=0x7FFFFFFF;
			for(int i=1;i<=N;i++)
				if(num[i])
					mn=min(mn,co[i].B/num[i]);
			for(int i=1;i<=N;i++)
				co[i].B-=num[i]*mn;
			ans+=mn;
		}
		else
			break;
	}
	while(1)
	{
		int sum=0;
		for(int i=1;i<=N;i++)
		{
			num[i]=min(co[i].B,(C-sum)/co[i].V);
			sum+=co[i].V*num[i];
		}
		for(int i=N;i>=1&&sum<C;i--)
			if(co[i].B-num[i])
			{
				num[i]++;
				sum+=co[i].V;
			}
		if(sum>=C)
		{
			int mn=0x7FFFFFFF;
			for(int i=1;i<=N;i++)
				if(num[i])
					mn=min(mn,co[i].B/num[i]);
			for(int i=1;i<=N;i++)
				co[i].B-=num[i]*mn;
			ans+=mn;
		}
		else
			break;
	}
	printf("%d\n",ans);
	return 0;
}
