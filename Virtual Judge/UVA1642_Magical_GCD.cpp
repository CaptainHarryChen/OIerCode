#include<cstdio>
#include<list>
#include<algorithm>
using namespace std;
const int MAXN=100005;

list<pair<long long,long long>> g;
long long A[MAXN];

int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&A[i]);
		long long ans=0;
		g.clear();
		for(int i=1;i<=n;i++)
		{
			for(auto &v:g)
				v.first=__gcd(v.first,A[i]);
			g.push_back(make_pair(A[i],i));
			auto it=g.begin(),j=g.begin();
			it++;
			while(it!=g.end())
			{
				if(it!=g.begin()&&it->first==j->first)
					it=g.erase(it);
				else
					it++,j++;
			}
			for(auto v:g)
				ans=max(ans,1LL*v.first*(i-v.second+1));
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
