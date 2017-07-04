#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXP 1000005
int prime[MAXP],cur;
bool noprime[MAXP];
int Set[MAXP];
bool vis[MAXP];
int Root(int x)
{return Set[x]==x?x:Set[x]=Root(Set[x]);}
int main()
{
	int C;
	scanf("%d",&C);
	noprime[1]=1;
	for(int i=2;i<MAXP;i++)
		if(!noprime[i])
		{
			prime[++cur]=i;
			if(i>1000)
				continue;
			for(int j=i*i;j<MAXP;j+=i)
				noprime[j]=1;
		}
	long long A,B,P;
	for(int Case=1;Case<=C;Case++)
	{
		scanf("%I64d%I64d%I64d",&A,&B,&P);
		for(int i=0;i<=B-A;i++)
			Set[i]=i,vis[i]=0;
		for(int i=lower_bound(prime+1,prime+cur+1,P)-prime;i<=cur&&prime[i]<=B;i++)
			for(long long j=((A+prime[i])/prime[i]-(A%prime[i]==0))*prime[i];j+prime[i]<=B;j+=prime[i])
			{
				int r1=Root((int)(j-A)),r2=Root((int)(j-A+prime[i]));
				Set[r2]=r1;
			}
		int ans=0;
		for(int i=0;i<=B-A;i++)
			if(!vis[Root(i)])
			{
				vis[Root(i)]=1;
				ans++;
			}
		printf("Case #%d: %d\n",Case,ans);
	}
	return 0;
}
