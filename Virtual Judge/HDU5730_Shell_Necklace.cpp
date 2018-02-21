#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<complex>
using namespace std;
const int MAXN=500005,MOD=313;
const double PI=acos(-1);
typedef complex<double> cpxd;
	
void FFT(cpxd A[],int len,int mode)
{
	for(int i=0,j=0;i<len;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=len>>1;
		while(k&&(k&j))
		{
			j^=k;
			k>>=1;
		}
		j^=k;
	}
	for(int i=1;i<len;i<<=1)
		for(int j=0;j<i;j++)
		{
			cpxd w=exp(cpxd(0,mode*2.0*PI*(1.0*j/(i*2.0))));
			for(int l=j,r=j+i;l<len;l+=(i<<1),r=l+i)
			{
				cpxd temp=w*A[r];
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
		}
	if(mode==-1)
		for(int i=0;i<len;i++)
			A[i]/=len;
}

cpxd A[MAXN],B[MAXN];
void mul(const int *a,int len1,const int *b,int len2,int *c)
{
	int len=1;
	while(len<len1+len2)
		len<<=1;
	memset(A,0,sizeof(cpxd)*len);
	memset(B,0,sizeof(cpxd)*len);
	for(int i=0;i<len1;i++)
		A[i]=1.0*a[i];
	for(int i=0;i<len2;i++)
		B[i]=1.0*b[i];
	FFT(A,len,1);
	FFT(B,len,1);
	for(int i=0;i<len;i++)
		A[i]=A[i]*B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++)
		c[i]=(int)floor(A[i].real()+0.5);
}

int a[MAXN],dp[MAXN],pro[MAXN];

void CDQ(int l,int r)
{
	if(l>=r)
	{
		if(l==0)
			dp[l]=1;
		return;
	}
	int mid=(l+r)/2;
	CDQ(l,mid);
	mul(dp+l,mid-l+1,a+1,r-l,pro+l+1);
	for(int i=mid+1;i<=r;i++)
		dp[i]=(dp[i]+pro[i])%MOD;
	CDQ(mid+1,r);
}

int main()
{
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			a[i]%=MOD;
		}
		memset(dp,0,sizeof(int)*(n+1));
		CDQ(0,n);
		printf("%d\n",dp[n]);
	}
	return 0;
}
