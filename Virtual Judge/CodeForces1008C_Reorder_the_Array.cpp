#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN=100005;

int n;
int A[MAXN];
set< pair<int,int> > S;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",A+i);
		S.insert(make_pair(A[i],i));
	}
	sort(A+1,A+n+1);
	int ans=0;
	for(int i=n;i>=1;i--)
	{
		set< pair<int,int> >::iterator it;
		it=S.lower_bound(make_pair(A[i],0));
		if(it->first>=A[i])
		{
			if(it==S.begin())
				break;
			it--;
		}
		ans++;
		S.erase(it);
	}
	printf("%d\n",ans);
	
	return 0;
}
