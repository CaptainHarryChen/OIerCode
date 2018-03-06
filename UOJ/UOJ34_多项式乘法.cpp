#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=400005,MOD=998244353,G=3;

int pow_mod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

void NTT(int A[],int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=(n>>1);
		while(k&&(k&j))
		{
			j^=k;
			k>>=1;
		}
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
	{
		int w1=pow_mod(G,(MOD-1)/(i<<1)),w=1;
		if(mode==-1)
			w1=pow_mod(w1,MOD-2);
		for(int j=0;j<i;j++,w=(1LL*w*w1)%MOD)
			for(int l=j,r=l+i;l<n;l+=(i<<1),r=l+i)
			{
				int temp=(1LL*A[r]*w)%MOD;
				A[r]=(A[l]-temp+MOD)%MOD;
				A[l]=(A[l]+temp)%MOD;
			}
	}
	if(mode==-1)
	{
		int inv=pow_mod(n,MOD-2);
		for(int i=0;i<n;i++)
			A[i]=(1LL*A[i]*inv)%MOD;
	}
}

void mul(const int A[],int l1,const int B[],int l2,int C[])
{
	static int tA[MAXN],tB[MAXN];
	int len=1;
	while(len<l1+l2-1)
		len<<=1;
	for(int i=0;i<len;i++)
		tA[i]=tB[i]=0;
	for(int i=0;i<l1;i++)
		tA[i]=A[i];
	for(int i=0;i<l2;i++)
		tB[i]=B[i];
	NTT(tA,len,1);
	NTT(tB,len,1);
	for(int i=0;i<len;i++)
		tA[i]=(1LL*tA[i]*tB[i])%MOD;
	NTT(tA,len,-1);
	for(int i=0;i<len;i++)
		C[i]=tA[i];
}

int A[MAXN],B[MAXN];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
		scanf("%d",A+i);
	for(int i=0;i<=m;i++)
		scanf("%d",B+i);
	mul(A,n+1,B,m+1,A);
	for(int i=0;i<n+m;i++)
		printf("%d ",A[i]);
	printf("%d\n",A[n+m]);
	return 0;
}
