#include<cstdio>
#include<cstring>
const int MAXN=40;

int dp[MAXN][MAXN];
char str[MAXN];
int len[MAXN];

int main()
{
	int n,k,m,s;
	scanf("%d%d%d%d",&n,&k,&m,&s);
	
	dp[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m&&k<=j;k++)
				dp[i][j]+=dp[i-1][j-k];
	printf("%d\n",dp[k][n]);
	for(int i=1;i<=s;i++)
	{
		scanf("%s",str);
		memset(len,0,sizeof len);
		len[1]=1;
		for(int j=1,p=1;j<n;j++)
			if(str[j]==str[j-1])
				len[p]++;
			else
				len[++p]=1;
		int ans=0,cnt=0;
		for(int j=1;j<=k;j++)
		{
			if(j&1)
				for(int p=1;p<len[j];p++)
					ans+=dp[k-j][n-cnt-p];
			else
				for(int p=len[j]+1;p+cnt<=n&&p<=m;p++)
					ans+=dp[k-j][n-cnt-p];
			cnt+=len[j];
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
