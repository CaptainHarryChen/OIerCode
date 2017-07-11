#include<cstdio>
#include<cstring>
const long long MAXD=12,MAXN=10;
long long dp[MAXD][MAXN],d[MAXD];
void Init_DP()
{
	d[0]=1;
	for(long long j=0;j<MAXN;j++)
		d[1]+=(dp[1][j]=1);
	for(long long i=2;i<MAXD;i++)
		for(long long j=0;j<MAXN;j++)
		{
			for(long long k=0;k<MAXN;k++)
				if(k<=j-2||k>=j+2)
					dp[i][j]+=dp[i-1][k];
			if(j>0)
				d[i]+=dp[i][j];
			else
				d[i]+=d[i-1];
		}
}
long long solve(long long x)
{
	long long ret=0,len;
	char s[MAXD];
	sprintf(s,"%lld",x);
	len=strlen(s);
	bool suc=1;
	for(long long i=0;i<len&&suc;i++)
	{
		for(long long j=0;j<s[i]-'0';j++)
		{
			if(j==0&&i==0)
				ret+=d[len-1];
			else if(i<=0||s[i-1]-'0'<=j-2||s[i-1]-'0'>=j+2)
				ret+=dp[len-i][j];
		}
		if(i>=0&&s[i]>s[i-1]-2&&s[i]<s[i-1]+2)
			suc=0;
	}
	if(suc)
		ret++;
	return ret;
}
int main()
{
	Init_DP();
	long long A,B;
	scanf("%lld%lld",&A,&B);
	printf("%lld\n",solve(B)-solve(A-1));
	return 0;
}
