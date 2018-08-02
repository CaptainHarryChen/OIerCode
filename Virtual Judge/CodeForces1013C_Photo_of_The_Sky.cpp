#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n;
int A[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++)
		scanf("%d",&A[i]);
	
	sort(A+1,A+n*2+1);
	
	long long s=1LL*(A[n]-A[1])*(A[n*2]-A[n+1]);
	for(int i=2;i+n-1<n*2;i++)
		s=min(s,1LL*(A[i+n-1]-A[i])*(A[n*2]-A[1]));
	printf("%I64d\n",s);
	
	return 0;
}
