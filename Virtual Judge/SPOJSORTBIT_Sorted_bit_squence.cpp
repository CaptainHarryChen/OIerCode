#include<cstdio>
#include<cstring>
int dp[35][35][2];
void Init()
{
	dp[0][0][0]=1;
	for(int i=1;i<=32;i++)
		for(int j=0;j<=i;j++)
		{
			if(j<i)
				dp[i][j][0]+=dp[i-1][j][0]+dp[i-1][j][1];
			if(j>0)
				dp[i][j][1]+=dp[i-1][j-1][0]+dp[i-1][j-1][1];
		}
}
void GetRanks(unsigned int x,int r[])
{
	int len=32,cnt=0;
	unsigned int t=1U<<31U;
	while(len>0&&(x&t)==0)
		len--,t>>=1U;
	for(int i=len;i>0;i--,t>>=1U)
		if(x&t)
		{
			for(int j=0;j<=i;j++)
				r[j+cnt]+=dp[i][j][0];
			cnt++;
		}
}
int GetRank(unsigned int x,int num1)
{
	int len=32,cnt=0,ret=0;
	unsigned t=1U<<31U;
	while(len>0&&(x&t)==0)
		len--,t>>=1U;
	for(int i=len;i>0;i--,t>>=1U)
		if(x&t)
		{
			ret+=dp[i][num1-cnt][0];
			cnt++;
		}
	return ret;
}
int ns[35],ms[35];
int main()
{
	Init();
	unsigned int n,m,mid;
	int T,k,s,tmp;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%u%u%d",&n,&m,&k);
		memset(ns,0,sizeof ns);
		memset(ms,0,sizeof ms);
		GetRanks(n,ns);
		GetRanks(m+1U,ms);
		tmp=0;
		for(s=0;s<=32&&tmp<k;s++)
		{
			if(tmp+ms[s]-ns[s]>=k)
				break;
			tmp+=ms[s]-ns[s];
		}
		k-=tmp;
		while(n<m)
		{
			mid=(n+((m-n)>>1U));
			if(GetRank(mid,s)-ns[s]>=k)
				m=mid;
			else
				n=mid+1;
		}
		printf("%d\n",n-1);
	}
	return 0;
}
