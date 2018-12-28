#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=305;

int n;
char s[MAXN];
pair<int,pair<int,int> > P[MAXN];
int dp[MAXN*MAXN];

bool cmp(pair<int,pair<int,int> > A,pair<int,pair<int,int> > B)
{
	pair<int,int> a=A.second,b=B.second;
	if(a.second>=a.first)
	{
		if(b.second<b.first)
			return true;
		return a.first<b.first;
	}
	else
	{
		if(b.second>=b.first)
			return false;
		return a.second>b.second;
	}
	return false;
}

int main()
{
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		int len=strlen(s),a=0,b=0;
		for(int j=0;j<len;j++)
			if(s[j]=='(')
				b++;
			else
			{
				if(b)
					b--;
				else
					a++;
			}
		P[i]=make_pair(len,make_pair(a,b));
		sum+=len;
	}
	sort(P+1,P+n+1,cmp);
	
	memset(dp,0xC0,sizeof dp);
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		if(P[i].second.first>P[i].second.second)
		{
			for(int j=P[i].second.first;j<=sum;j++)
				dp[j+P[i].second.second-P[i].second.first]=max(dp[j+P[i].second.second-P[i].second.first]
																,dp[j]+P[i].first);
		}
		else
		{
			for(int j=sum;j>=P[i].second.first;j--)
				dp[j+P[i].second.second-P[i].second.first]=max(dp[j+P[i].second.second-P[i].second.first]
																,dp[j]+P[i].first);
		}
	}
	printf("%d\n",dp[0]);
	
	return 0;
}
