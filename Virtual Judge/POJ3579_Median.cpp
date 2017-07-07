#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int n,num[MAXN];
bool check(int mid)
{
	long long cnt=0;
	for(int i=1,j=2;i<=n&&j<=n&&!(i==n&&j==n);)
	{
		if(num[j]-num[i]<=mid)
			while(num[j]-num[i]<=mid&&j<=n)
			{
				cnt+=j-i;
				j++;
			}
		else if(num[j]-num[i]>mid||j==n)
			while(num[j]-num[i]>mid&&i<=j)
				i++;
	}
	return cnt>=(1LL*n*(n-1)/2LL+1)/2LL;
}
int main()
{
	int L,R,mid;
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",num+i);
		sort(num+1,num+n+1);
		L=0x7FFFFFFF;
		for(int i=1;i<n;i++)
			L=min(L,num[i+1]-num[i]);
		R=num[n]-num[1];
		while(L<R)
		{
			mid=(L+R)/2;
			if(check(mid))
				R=mid;
			else
				L=mid+1;
		}
		printf("%d\n",L);
	}
	return 0;
}
