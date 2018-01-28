#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXL1=105,MAXL2=3005;

char A[MAXL1],B[MAXL1],S[MAXL2];
int dp[MAXL2][MAXL1];
vector< pair<int,int> > Sa,Sb;

void FindS(const char *A,vector< pair<int,int> > &res)
{
	memset(dp,-1,sizeof dp);
	int lA=strlen(A),lS=strlen(S);
	for(int i=0;i<lS;i++)
	{
		for(int j=0;j<lA;j++)
		{
			int t=-1;
			if(i>0&&j>0&&dp[i-1][j-1]!=-1&&S[i]==A[j])
				t=max(t,dp[i-1][j-1]);
			if(i>0&&dp[i-1][j]!=-1)
				t=max(t,dp[i-1][j]);
			if(j==0&&S[i]==A[0])
				t=i;
			dp[i][j]=t;
		}
	}
	for(int i=0;i<lS;i++)
		if(S[i]==A[lA-1]&&dp[i][lA-1]!=-1)
			res.push_back(make_pair(dp[i][lA-1],i));
}

int main()
{
	scanf("%s%s%s",A,B,S);
	FindS(A,Sa);
	FindS(B,Sb);
	int s1=Sa.size(),s2=Sb.size(),ans=strlen(S);
	if(s1==0||s2==0)
		ans=-1;
	else
		for(int i=0;i<s1;i++)
			for(int j=0;j<s2;j++)
				ans=min(ans,max(Sa[i].second,Sb[j].second)-min(Sa[i].first,Sb[j].first)+1);
	printf("%d\n",ans);
	return 0;
}
