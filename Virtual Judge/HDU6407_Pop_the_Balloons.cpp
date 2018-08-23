#include<cstdio>
#define int __int128
const int MAXM=15,MAXN=23,MAXS=(1<<12)+10,MAXK=23;

template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}

int m,n,k;
int dp[MAXN][MAXS];
int ball[MAXN];
char str[MAXM][MAXN];
int ans[MAXN];

#undef int __int128
int main()
#define int __int128
{
	int T;
	Read(T);
	while(T--)
	{
		Read(m);Read(n);Read(k);
		for(int j=1;j<=n;j++)
			ball[j]=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%s",str[i]+1);
			for(int j=1;j<=n;j++)
				if(str[i][j]=='Q')
					ball[j]|=(1<<(i-1));
		}
		for(int i=1;i<=k;i++)
			ans[i]=0;
		for(int mask1=1;mask1<(1<<m);mask1++)
		{
			dp[0][0]=1;
			for(int i=0;i<n;i++)
				for(int mask2=mask1;mask2>=0;mask2=(mask2-1)&mask1)
				{
					if(dp[i][mask2])
					{
						//printf("dp[%d][%d]=%d\n",i,mask2,dp[i][mask2]);
						if((ball[i+1]&mask1)==ball[i+1])
							dp[i+1][mask2]+=dp[i][mask2];
						int tmask=(((1<<m)-1)^mask2)&ball[i+1]&mask1;
						for(int s=tmask&(-tmask);tmask>0;tmask^=(tmask&(-tmask)),s=tmask&(-tmask))
							dp[i+1][s|mask2]+=dp[i][mask2];
					}
					if(mask2==0)
						break;
				}
			ans[__builtin_popcount(mask1)]+=dp[n][mask1];
			for(int i=1;i<=n;i++)
				for(int mask2=mask1;mask2>=0;mask2=(mask2-1)&mask1)
				{
					dp[i][mask2]=0;
					if(mask2==0)
						break;
				}
		}
		int fac=1;
		for(int i=1;i<=k;i++)
		{
			fac*=i;
			ans[i]*=fac;
			int j;
			for(j=1;j*10<=ans[i];j*=10);
			while(j)
			{
				putchar(ans[i]/j+'0');
				ans[i]%=j;
				j/=10;
			}
			putchar('\n');
		}
	}
	
	return 0;
}
