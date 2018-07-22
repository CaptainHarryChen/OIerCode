#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=1000005,MOD=998244353;

int n;
int a[MAXN];
int pow2[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	pow2[0]=1;
	for(int i=1;i<n;i++)
		pow2[i]=(1LL*pow2[i-1]*2LL)%MOD;
		
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int tmp=pow2[n-i];
		if(i<n)
			tmp=(tmp+1LL*pow2[n-i-1]*(n-i)%MOD)%MOD;
		ans+=1LL*a[i]*tmp%MOD;
		ans%=MOD;
	}
	printf("%d\n",ans);
	
	return 0;
}
