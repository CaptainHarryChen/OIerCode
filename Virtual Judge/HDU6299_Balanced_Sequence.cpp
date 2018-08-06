#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

char s[MAXN];
pair<int,int> A[MAXN];

bool cmp(pair<int,int> a,pair<int,int> b)
{
	if(a.second>a.first&&b.second<=b.first)
		return true;
	if(a.second<=a.first&&b.second>b.first)
		return false;
	if(a.second>a.first)
		return a.first<b.first;
	return a.second>b.second;
}

int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		int ans=0;
		int cnt1,cnt2;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s);
			int m=strlen(s);
			cnt1=0,cnt2=0;
			for(int j=0;j<m;j++)
				if(s[j]==')')
				{
					if(cnt2==0)
						cnt1++;
					else
						cnt2--,ans+=2;
				}
				else
					cnt2++;
			A[i].first=cnt1;
			cnt1=cnt2=0;
			for(int j=m-1;j>=0;j--)
				if(s[j]=='(')
				{
					if(cnt2==0)
						cnt1++;
					else
						cnt2--;
				}
				else
					cnt2++;
			A[i].second=cnt1;
		}
		sort(A+1,A+n+1,cmp);
		cnt1=0;
		for(int i=1;i<=n;i++)
		{
			int delta=min(cnt1,A[i].first);
			ans+=delta*2;
			cnt1-=delta;
			cnt1+=A[i].second;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
