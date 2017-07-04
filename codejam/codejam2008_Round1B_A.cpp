#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXN 100005
int main()
{
	int N,Case,n,cnt[9];
	long long A,B,C,D,x0,y0,M;
	scanf("%d",&N);
	for(Case=1;Case<=N;Case++)
	{
		for(int i=0;i<9;i++)
			cnt[i]=0;
		scanf("%d%I64d%I64d%I64d%I64d%I64d%I64d%I64d",&n,&A,&B,&C,&D,&x0,&y0,&M);
		int cur=1;
		do
		{
			cnt[x0%3LL*3LL+y0%3LL]++;
			x0=(A*x0+B)%M;
			y0=(C*y0+D)%M;
			cur++;
		}while(cur<=n);
		long long ans=0;
		for(int i=0;i<9;i++)
		{
			if(!cnt[i])continue;
			for(int j=i;j<9;j++)
			{
				if(!cnt[j])continue;
				int k=(9-i/3-j/3)%3*3+(9-i%3-j%3)%3;
				if(!cnt[k]||k<j)continue;
				if(i==j&&j==k&&k==i)
				{
					if(cnt[i]<3)continue;
					ans+=1LL*cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6;
				}
				else
					ans+=1LL*cnt[i]*cnt[j]*cnt[k];
			}
		}
		printf("Case #%d: %I64d\n",Case,ans);
	}
	return 0;
}
