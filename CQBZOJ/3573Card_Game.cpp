#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXV=(1<<18)+10;

int N,M,Q;
int A[MAXV],B[MAXV];

void FWT(int A[],int n,int mode)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<i;j++)
			for(int l=j,r=j+i;l<n;l+=(i<<1),r=l+i)
				A[r]+=mode*A[l];
}

void mul(int A[],int l1,int B[],int l2)
{
	int n=1;
	if(l1<l2)swap(l1,l2);
	while(n<l1)
		n<<=1;
	FWT(A,n,1);
	FWT(B,n,1);
	for(int i=1;i<=n;i++)
		A[i]=A[i]*B[i];
	FWT(A,n,-1);
}

int trans(long long x)
{
	int ret=0;
	for(int j=1;x;j<<=1,x/=10)
		if(x%10==1)
			ret|=j;
	return ret;
}

int main()
{
	int T;
	long long a;
	scanf("%d",&T);
	for(int cas=1;cas<=T;cas++)
	{
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++)
		{
			scanf("%lld",&a);
			A[trans(a)]++;
		}
		for(int i=1;i<=N;i++)
		{
			scanf("%lld",&a);
			B[trans(a)]++;
		}
		mul(A,1<<M,B,1<<M);
		scanf("%d",&Q);
		printf("Case #%d:\n",cas);
		while(Q--)
		{
			scanf("%lld",&a);
			a=trans(a);
			printf("%d\n",A[a]);
		}
	}
	return 0;
}
