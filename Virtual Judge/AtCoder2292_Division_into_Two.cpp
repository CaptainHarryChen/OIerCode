#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=1000000007;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;

int N;
long long A,B,S[MAXN];
int f[MAXN],sum[MAXN];

int main()
{
	scanf("%d%lld%lld",&N,&A,&B);
	for(int i=1;i<=N;i++)
		scanf("%lld",&S[i]);
	if(A>B)
		swap(A,B);
	for(int i=3;i<=N;i++)
		if(S[i]-S[i-2]<A)
		{
			puts("0");
			return 0;
		}
	S[N+1]=LLF;
	
	f[0]=sum[0]=1;
	int l=0,r=0;
	for(int i=1;i<=N+1;i++)
	{
		while(r<i-1&&S[i]-S[r+1]>=B)
			r++;
		if(l<=r)
			(f[i]+=(sum[r]-(l==0?0:sum[l-1])+MOD)%MOD)%=MOD;
		sum[i]=(sum[i-1]+f[i])%MOD;
		if(i!=1&&S[i]-S[i-1]<A)
			l=i-1;
	}
	printf("%d\n",f[N+1]);
	
	return 0;
}
