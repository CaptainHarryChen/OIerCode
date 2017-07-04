#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXQ 1005
#define MAXS 105
int N,S,Q;
char si[MAXQ][MAXS],qi[MAXQ][MAXS];
pair<int,int>sear[MAXQ*MAXS];
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d\n",&N);
	for(int Case=1;Case<=N;Case++)
	{
		scanf("%d\n",&S);
		for(int i=1;i<=S;i++)
			gets(si[i]);
		scanf("%d\n",&Q);
		for(int i=1;i<=Q;i++)
			gets(qi[i]);
		int cur=0,last;
		for(int i=1;i<=S;i++)
		{
			last=0;
			for(int j=1;j<=Q;j++)
				if(strcmp(si[i],qi[j])==0)
				{
					if(j-1>=last+1)
					{
						cur++;
						sear[cur]=make_pair(last+1,j-1);
					}
					last=j;
				}
			if(Q>=last+1)
			{
				cur++;
				sear[cur]=make_pair(last+1,Q);
			}
		}
		sort(sear+1,sear+cur+1);
		int now=1,ans=0,k=1;
		while(now<=Q)
		{
			int mx=-1;
			for(;k<=cur&&sear[k].first<=now;k++)
				mx=max(mx,sear[k].second);
			if(mx==-1)
				break;
			ans++;
			now=mx+1;
		}
		printf("Case #%d: %d\n",Case,max(ans-1,0));
	}
	return 0;
}
