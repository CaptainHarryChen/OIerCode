#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=22,MAXS=(1<<20)+10,MOD=998244353;

int n,A[MAXN];

int sum[MAXS],f[MAXS],g[MAXS],h[MAXS];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	
	
	for(int s=1;s<(1<<n);s++)
		for(int i=1;i<=n;i++)
			if(s&(1<<(i-1)))
				sum[s]+=A[i];
	
	f[0]=1;
	for(int s=0;s<(1<<n);s++)
		if(f[s])
			for(int i=1;i<=n;i++)
				if((s&(1<<(i-1)))==0&&sum[s^(1<<(i-1))]>0)
					(f[s^(1<<(i-1))]+=f[s])%=MOD;
	memcpy(h,f,sizeof f);
	for(int s=0;s<(1<<n);s++)
		if(f[s])
			for(int i=1;i<=n;i++)
				if((s&(1<<(i-1)))==0&&A[i]+sum[s]<0)
					(h[s^(1<<(i-1))]+=f[s])%=MOD;
	g[0]=1;
	for(int s=0;s<(1<<n);s++)
		if(g[s])
			for(int i=1;i<=n;i++)
				if((s&(1<<(i-1)))==0&&sum[s^(1<<(i-1))]<=0)
					(g[s^(1<<(i-1))]+=g[s])%=MOD;
	
	int ans=0;
	for(int s=1;s<(1<<n);s++)
		ans=(ans+1LL*sum[s]*h[s]%MOD*g[((1<<n)-1)^s]%MOD+MOD)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
