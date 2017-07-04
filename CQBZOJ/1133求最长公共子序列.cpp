#include<iostream>
#include<cstring>
#define MAXN 1010
using namespace std;
char s1[MAXN],s2[MAXN];
int len1,len2,dp[MAXN][MAXN];
void print_ans(int x,int y)
{
	if(x>=len1&&y>=len2)return;
	if(s1[x]==s2[y])
	{
		cout<<s1[x];
		print_ans(x+1,y+1);
	}
	else
	{
		if(dp[x+1][y]>dp[x][y+1])
			print_ans(x+1,y);
		else
			print_ans(x,y+1);
	}
}
int main()
{
	cin>>(s1+1)>>(s2+1);
	len1=strlen(s1+1);
	len2=strlen(s2+1);
	for(int i=len1;i>0;i--)
		for(int j=len2;j>0;j--)
		{
			dp[i][j]=dp[i+1][j];
			dp[i][j]=max(dp[i][j],dp[i][j+1]);
			if(s1[i]==s2[j])
				dp[i][j]=max(dp[i][j],dp[i+1][j+1]+1);
		}
	cout<<dp[1][1]<<endl;
	print_ans(1,1);
	cout<<endl;
	return 0;
}
