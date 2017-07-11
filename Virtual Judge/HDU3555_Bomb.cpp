#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXD=25,MAXN=10;
char num[MAXD];
long long dp[MAXD][MAXN];
int main()
{
	dp[0][0]=1LL;
	for(int i=1;i<MAXD;i++)
		for(int j=0;j<MAXN;j++)
			for(int k=0;k<MAXN;k++)
				if(j!=4||k!=9)
					dp[i][j]+=dp[i-1][k];
	int T,len;
	long long ans;
	bool suc;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",num);
		len=strlen(num);
		ans=0;
		suc=1;
		for(int i=0;i<len&&suc;i++)
		{
			for(int j=0;j<num[i]-'0';j++)
				if(i==0||num[i-1]!='4'||j!=9)
					ans+=dp[len-i][j];
			if(i>0&&num[i]=='9'&&num[i-1]=='4')
				suc=0;
		}
		if(suc)ans++;
		ans--;
		long long n=0;
		for(int i=0;i<len;i++)
			n=n*10+num[i]-'0';
		printf("%I64d\n",n-ans);
	}
	return 0;
}
