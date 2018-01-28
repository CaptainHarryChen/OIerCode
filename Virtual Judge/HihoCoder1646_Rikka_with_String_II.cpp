#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=22,MAXL=53,MOD=998244353;

char s[MAXN][MAXL];
int len[MAXN];
int pow2[MAXN*MAXL];

int main()
{
	pow2[0]=1;
	for(int i=1;i<MAXN*MAXL;i++)
		pow2[i]=(pow2[i-1]*2)%MOD;
	
	int n,numq=0,sumlen=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]);
		len[i]=strlen(s[i]);
		sumlen+=len[i];
		for(int j=0;j<len[i];j++)
			numq+=(s[i][j]=='?');
	}
	
	int ans=(1LL*sumlen*pow2[numq])%MOD;
	for(int S=0;S<(1<<n);S++)
	{
		if(__builtin_popcount(S)<2)
			continue;
		int minlen=MAXL;
		for(int i=1;i<=n;i++)
			if((S>>(i-1))&1)
				minlen=min(minlen,len[i]);
		int restq=numq;
		for(int i=0;i<minlen;i++)
		{
			int type=-1,cntq=0;
			for(int j=1;j<=n;j++)
				if((S>>(j-1))&1)
				{
					if(s[j][i]=='?')
						cntq++;
					else if(type!=-1)
					{
						if(type!=s[j][i]-'0')
						{
							type=2;
							break;
						}
					}
					else
						type=s[j][i]-'0';
				}
			if(type==2)
				break;
			restq-=cntq;
			if(type==-1)
				restq++;//假装加了一个?,实际上是为了*2
			int delta=pow2[restq];
			if(__builtin_popcount(S)%2==0)
				delta=MOD-delta;
			ans=(ans+delta)%MOD;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}
