#include<cstdio>
#include<cstring>
const int MAXD=17,MAXN=10;
long long dp[MAXD][MAXN],dp2[MAXD],pow10[MAXD]={1,10};
void Init()
{
	for(int j=0;j<MAXN;j++)
		dp[1][j]=j;
	dp2[1]=5;
	pow10[0]=1;
	for(int i=2;i<MAXD;i++)
	{
		pow10[i]=pow10[i-1]*10LL;
		dp2[i]+=dp2[i-1];
		if(i%2==1)
			dp2[i]+=5LL*(pow10[i-1]-pow10[i-2]);
		for(int j=0;j<MAXN;j++)
		{
			for(int k=0;k<MAXN;k++)
				dp[i][j]+=1LL*j*pow10[i-2]-dp[i-1][k];
			if(j>0&&i%2==0)
				dp2[i]-=dp[i][j];
		}
	}
}
long long solve(char num[],int len)
{
	long long ret=0;
	int tmp=0,f;
	if(len%2==0)
	{
		f=-1;
		for(int i=len;i>0;i--)
		{
			for(int j=0;j<num[len-i]-'0';j++)
				if(i==len&&j==0)
					ret+=dp2[i-1];
				else
					ret+=dp[i][j]*f+tmp*pow10[i-1];
			tmp+=(num[len-i]-'0')*f;
			if(f==-1)f=1;
			else f=-1;
		}
		ret+=tmp;
	}
	else
	{
		f=1;
		for(int i=len;i>0;i--)
		{
			for(int j=0;j<num[len-i]-'0';j++)
				if(i==len&&j==0)
					ret+=dp2[i-1];
				else
				{
					if(i>1)
						ret+=pow10[i-1]/2;
					else
					{
						if(len%2==1&&j%2==1)
							ret+=tmp+j;
						else
							ret+=-tmp-j;
					}
				}
			tmp+=(num[len-i]-'0')*f;
			if(f==-1)f=1;
			else f=-1;
		}
		if(len%2==1&&(num[len-1]-'0')%2==1)
			ret+=tmp;
		else
			ret+=-tmp;
	}
	return ret;
}
int main()
{
	Init();
	char N[MAXD]="";
	int len=0;
	while(1)
	{
		scanf("%s",N);
		len=strlen(N);
		if(len==1&&N[0]=='0')
			break;
		printf("%lld\n",solve(N,len));
	}
	return 0;
}
