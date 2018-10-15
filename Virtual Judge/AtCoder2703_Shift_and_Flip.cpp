#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
const int MAXN=2005;

int N;
char A[MAXN],B[MAXN];
int left[MAXN],right[MAXN];
vector<pair<int,int>> range;
int best[MAXN];

int main()
{
	scanf("%s%s",A+1,B+1);
	N=strlen(A+1);
	
	bool flag=false;
	for(int i=1;i<=N&&!flag;i++)
		if(B[i]=='1')
			flag=true;
	if(!flag)
	{
		flag=true;
		for(int i=1;i<=N&&flag;i++)
			if(A[i]=='1')
				flag=false;
		if(!flag)
			puts("-1");
		else
			puts("0");
		return 0;
	}
	
	for(int i=1;i<=N;i++)
	{
		while(B[(i-left[i]-1+N)%N+1]!='1')
			left[i]++;
		while(B[(i+right[i]-1)%N+1]!='1')
			right[i]++;
	}
	int ans=0x3F3F3F3F;
	for(int i=0;i<N;i++)
	{
		int tmp=0;
		range.clear();
		for(int j=1;j<=N;j++)
			if(A[j]!=B[(j-i-1+N)%N+1])
			{
				tmp++;
				if(A[j]=='1')
					range.emplace_back(left[j],right[j]);
			}
		if(range.size()==0U)
		{
			ans=min(ans,tmp+i);
			continue;
		}
		sort(range.begin(),range.end(),greater<pair<int,int>>());
		best[0]=range[0].second;
		for(int i=1;i<(int)range.size();i++)
			best[i]=max(best[i-1],range[i].second);
		int p=range.size()-1;
		for(int l=i;l<N;l++)
		{
			while(p>=0&&range[p].first<=l)
				p--;
			int r=p==-1?0:best[p];
			ans=min(ans,tmp+r*2+l+(l-i));
		}
	}
	for(int i=0;i<N;i++)
	{
		int tmp=0;
		range.clear();
		for(int j=1;j<=N;j++)
			if(A[j]!=B[(j+i-1)%N+1])
			{
				tmp++;
				if(A[j]=='1')
					range.emplace_back(right[j],left[j]);
			}
		if(range.size()==0U)
		{
			ans=min(ans,tmp+i);
			continue;
		}
		sort(range.begin(),range.end(),greater<pair<int,int>>());
		best[0]=range[0].second;
		for(int i=1;i<(int)range.size();i++)
			best[i]=max(best[i-1],range[i].second);
		int p=range.size()-1;
		for(int r=i;r<N;r++)
		{
			while(p>=0&&range[p].first<=r)
				p--;
			int l=p==-1?0:best[p];
			ans=min(ans,tmp+l*2+r+(r-i));
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
