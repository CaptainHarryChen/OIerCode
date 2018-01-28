#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

priority_queue< int,vector<int>,greater<int> > Q;

int main()
{
	int n,a;
	long long ans=0LL;
	scanf("%d",&n);
	scanf("%d",&a);
	Q.push(a);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&a);
		Q.push(a);
		int mn=Q.top();
		if(mn<a)
		{
			Q.pop();
			ans+=1LL*(a-mn);
			Q.push(a);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
