#include<cstdio>
#include<functional>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n;
pair<int,long long> A[MAXN],B[70];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%d",&A[i].second,&A[i].first);
	sort(A+1,A+n+1,greater<pair<int,int> >());
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		long long x=A[i].second;
		int k=62;
		while((x&(1LL<<k))==0)
			k--;
		for(;k>=0;k--)
			if(x&(1LL<<k))
			{
				if(B[k].first==0)
				{
					ans+=A[i].first;
					B[k]=make_pair(A[i].first,x);
					break;
				}
				x^=B[k].second;
			}
	}
	printf("%d\n",ans);
	
	return 0;
}
