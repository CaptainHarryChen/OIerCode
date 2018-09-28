#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n,A[MAXN];

bool solve()
{
	if(n==1)
		return false;
	int cnt[2]={0,0};
	for(int i=1;i<=n;i++)
		cnt[A[i]&1]++;
	if(cnt[0]&1)
		return true;
	if((cnt[0]&1)==0&&cnt[1]>=2)
		return false;
	int pos=-1;
	for(int i=1;i<=n&&pos==-1;i++)
		if(A[i]&1)
			pos=i;
	if(A[pos]==1)
	{
		int sum=0;
		for(int i=1;i<=n;i++)
			sum^=(A[i]-1)&1;
		return sum;
	}
	A[pos]--;
	int g=A[1];
	for(int i=2;i<=n;i++)
		g=__gcd(g,A[i]);
	for(int i=1;i<=n;i++)
		A[i]/=g;
	return solve()^1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	if(solve())
		puts("First");
	else
		puts("Second");
	
	return 0;
}
