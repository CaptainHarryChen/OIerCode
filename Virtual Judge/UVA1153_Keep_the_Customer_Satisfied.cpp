#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=800005;

int n;
pair<int,int> work[MAXN];
priority_queue<int> Q;
int ans;

int main()
{
	int T;
	int test=1;
	scanf("%d",&T);
	while(T--)
	{
		if(test!=1)
			puts("");
		test++;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&work[i].second,&work[i].first);
		sort(work+1,work+n+1);
		ans=0;
		int ti=0;
		while(!Q.empty())
			Q.pop();
		for(int i=1;i<=n;i++)
		{
			if(ti+work[i].second>work[i].first)
			{
				if(!Q.empty()&&Q.top()>work[i].second)
				{
					ti-=Q.top();
					Q.pop();
					Q.push(work[i].second);
					ti+=work[i].second;
				}
			}
			else
			{
				ti+=work[i].second;
				Q.push(work[i].second);
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
