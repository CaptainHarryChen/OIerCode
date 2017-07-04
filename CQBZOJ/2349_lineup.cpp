#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<map>
#define MAXN 100010
using namespace std;
map<int,int>cnts;
int cows[MAXN],n,k,ans,cnt;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&cows[i]);
	for(int i=1,j=0;j<=n&&i<=n;)
	{
		if(cnt<=k+1)
		{
			j++;
			if(!cnts[cows[j]])cnt++;
			cnts[cows[j]]++;
			if(cnts[cows[j]]>ans)
				ans=cnts[cows[j]];
		}
		else
		{
			if(cnts[cows[i]]==1)cnt--;
				cnts[cows[i]]--;
			i++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
