#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005;
int num[MAXN];
typedef pair<int,int> Ele;
typedef pair<int,Ele> Res;
Res s1[MAXN*MAXN],s2[MAXN*MAXN];
int st1,st2;
bool nodup(const Res &a,const Res &b)
{
	return a.second.first!=b.second.first
		&&a.second.first!=b.second.second
		&&a.second.second!=b.second.first
		&&a.second.second!=b.second.second;
}
int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(!n)
			break;
		for(int i=1;i<=n;i++)
			scanf("%d",num+i);
		st1=st2=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if(i==j)
					continue;
				s1[st1++]=Res(num[i]+num[j],Ele(i,j));
				s2[st2++]=Res(num[i]-num[j],Ele(i,j));
			}
		sort(s1,s1+st1);
		sort(s2,s2+st2);
		int ans=-0x7FFFFFFF;
		for(int i=0,j;i<st1;i++)
		{
			j=lower_bound(s2,s2+st2,Res(s1[i].first,Ele(0,0)))-s2;
			while(j<st2&&!nodup(s1[i],s2[j])&&s1[i].first==s2[j].first)
				j++;
			if(j>=st2||s1[i].first!=s2[j].first)
				continue;
			ans=max(ans,num[s2[j].second.first]);
		}
		if(ans==-0x7FFFFFFF)
			puts("no solution");
		else
			printf("%d\n",ans);
	}
	return 0;
}
