#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=300005;

long long N,A[MAXN],tmp[MAXN];
bool check(long long lim)
{
	for(long long i=1;i<=N;i++)
		tmp[i]=A[i];
	long long L=1,R=N,cnt=0;
	while(L<R)
	{
		while(L<R&&tmp[L]>=lim)
			cnt+=(tmp[L]==lim),L++;
		while(L<R&&tmp[R]<=lim+1)
			R--;
		if(L>=R)
			break;
		long long delta=min(lim-tmp[L],(tmp[R]-lim)/2);
		tmp[L]+=delta;
		tmp[R]-=delta*2;
	}
	while(tmp[R]>lim+1)
	{
		long long delta=(tmp[R]-lim)/3;
		tmp[R]-=delta*3;
		if(tmp[R]>lim+1)
		{
			if(cnt)
				tmp[R]=lim;
			else
				return false;
		}
	}
	if(tmp[L]<lim)
		return false;
	return true;
}

int main()
{
	long long T;
	scanf("%I64d",&T);
	while(T--)
	{
		scanf("%I64d",&N);
		long long L=0x7FFFFFFF,R=0;
		for(long long i=1;i<=N;i++)
			scanf("%I64d",&A[i]),R=max(R,A[i]),L=min(L,A[i]);
		sort(A+1,A+N+1);
		while(L<R)
		{
			long long mid=(L+R+1)/2;
			if(check(mid))
				L=mid;
			else
				R=mid-1;
		}
		if(!check(L))
			puts("-1");
		else
			printf("%I64d\n",L);
	}
	
	return 0;
}
