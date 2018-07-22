#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;
pair<int,int> P[MAXN];
priority_queue<int,vector<int>,greater<int> > Q;

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d%d",&P[i].second,&P[i].first);
		sort(P+1,P+n+1);
		while(!Q.empty())
			Q.pop();
		int t=1,ans=0;
		for(int i=1;i<=n;i++)
		{
			if(P[i].first>=t)
			{
				Q.push(P[i].second);
				ans+=P[i].second;
				t++;
			}
			else
			{
				int temp=Q.top();
				if(P[i].second>temp)
				{
					Q.pop();
					Q.push(P[i].second);
					ans+=P[i].second-temp;
				}
			}
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
