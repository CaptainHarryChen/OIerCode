#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000006;

int n,K;
pair<int,int> P[MAXN*2];
pair<int,int> ans[MAXN*2];
int top,cnt;

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		P[++top]=make_pair(l,1);
		P[++top]=make_pair(r+1,-1);
	}
	sort(P+1,P+top+1);
	int last=1;
	int L=-0x7FFFFFFF,k=0;
	for(int i=2,j;i<=top+1;i++)
		if(P[i].first!=P[i-1].first)
		{
			for(j=last;j<i&&P[j].second==-1;j++)
				k+=P[j].second;
			if(L!=-0x7FFFFFFF&&k<K)
				ans[++cnt]=make_pair(L,P[last].first-1),L=-0x7FFFFFFF;
			for(;j<i&&P[j].second==1;j++)
				k+=P[j].second;
			if(L==-0x7FFFFFFF&&k>=K)
				L=P[last].first;
			last=i;
		}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	
	return 0;
}