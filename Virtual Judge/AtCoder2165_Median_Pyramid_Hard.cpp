#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int N,A[MAXN],B[MAXN];
bool check(int x)
{
	for(int i=0;i<N-1;i++)
	{
		if(A[N+i]>=x&&A[N+i+1]>=x)
			return true;
		if(A[N-i]>=x&&A[N-i-1]>=x)
			return true;
		if(A[N+i]<x&&A[N+i+1]<x)
			return false;
		if(A[N-i]<x&&A[N-i-1]<x)
			return false;
	}
	if(A[1]>=x)
		return true;
	return false;
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=2*N-1;i++)
		scanf("%d",&A[i]);

	int L=1,R=2*N-1;
	while(L<R)
	{
		int mid=(L+R+1)/2;
		if(check(mid))
			L=mid;
		else
			R=mid-1;
	}
	printf("%d\n",L);
	return 0;
}
