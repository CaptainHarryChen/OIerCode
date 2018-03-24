#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=53;

class PointErasing
{
	vector<int> rect[MAXN];
	vector<int> p;
	bool dp[MAXN][MAXN];
	vector<int> DP(int l,int r,int line,vector<int> &y)
	{
		int n=y.size();
		p.clear();
		for(int i=0;i<n;i++)
			rect[i].clear();
		memset(dp,0,sizeof dp);
		for(int x=l;x<r;x++)
			if(y[x]==line)
				p.push_back(x);
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				if((y[i]<line&&line<y[j])||(y[i]>line&&line>y[j]))
				{
					int l=upper_bound(p.begin(),p.end(),i)-p.begin();
					int r=lower_bound(p.begin(),p.end(),j)-p.begin()-1;
					if(l<=r)
						rect[r+1].push_back(l+1);
				}
		dp[0][0]=true;
		for(int i=1;i<=(int)p.size();i++)
			for(int j=0;j<=i;j++)
			{
				if(j>0)
					dp[i][j]=dp[i-1][j-1];
				for(int k=0;k<(int)rect[i].size();k++)
					dp[i][j]|=dp[rect[i][k]-1][j];
			}
		vector<int> ans;
		for(int j=0;j<=(int)p.size();j++)
			if(dp[p.size()][j])
				ans.push_back(j);
		return ans;
	}
public:
	vector<int> getOutcomes(vector<int> &y)
	{
		int n=y.size();
		int miny=0x7FFFFFFF,maxy=0;
		for(int x=0;x<n;x++)
		{
			miny=min(miny,y[x]);
			maxy=max(maxy,y[x]);
		}
		int sec1=-1,sec2=-1,stay=0;
		for(int x=0;x<n;x++)
			if(y[x]==miny||y[x]==maxy)
			{
				if(sec1==-1)
					sec1=x;
				sec2=x;
				stay++;
			}
		vector<int> st1=DP(0,sec1,y[0],y);
		vector<int> st2=DP(sec2+1,n,y[n-1],y);
		vector<int> ans;
		for(int i=0;i<(int)st1.size();i++)
			for(int j=0;j<(int)st2.size();j++)
				ans.push_back(st1[i]+st2[j]+stay);
		sort(ans.begin(),ans.end());
		ans.resize(unique(ans.begin(),ans.end())-ans.begin());
		return ans;
	}
};

PointErasing solve;
vector<int> y,ans;

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		y.push_back(x);
	}
	ans=solve.getOutcomes(y);
	for(int i=0;i<(int)ans.size();i++)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}
