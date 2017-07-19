#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int> answer;
vector<answer> ans;
void solve(long long n)
{
	int l=1,r=1;
	long long sum=1LL;
	while(1LL*r*r<=n)
	{
		if(sum==n)
		{
			ans.push_back(make_pair(l,r));
			r++;
			sum+=1LL*r*r;
		}
		else if(sum<n)
		{
			r++;
			sum+=1LL*r*r;
		}
		else
		{
			sum-=1LL*l*l;
			l++;
		}
	}
}
int main()
{
	long long n;
	scanf("%lld",&n);
	solve(n);
	int sz=ans.size();
	printf("%d\n",sz);
	for(int i=0;i<sz;i++)
	{
		printf("%d ",ans[i].second-ans[i].first+1);
		for(int j=ans[i].first;j<ans[i].second;j++)
			printf("%d ",j);
		printf("%d\n",ans[i].second);
	}
	return 0;
}
