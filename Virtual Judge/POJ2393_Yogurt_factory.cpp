#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 10005
int N,S;
int C[MAXN],Y[MAXN];
int main()
{
	scanf("%d%d",&N,&S);
	scanf("%d%d",C+1,Y+1);
	for(int i=2;i<=N;i++)
	{
		scanf("%d%d",C+i,Y+i);
		C[i]=min(C[i],C[i-1]+S);
	}
	long long ans=0;
	for(int i=1;i<=N;i++)
		ans+=1LL*Y[i]*C[i];
	printf("%lld\n",ans);
	return 0;
}
