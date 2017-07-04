#include<cstdio>
#include<cstring>
#include<complex>
#include<cmath>
using namespace std;
const int MAXN=1000005;
typedef complex<double> cpxd;
void FFT(cpxd *A,int n,int flag)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(j>i)swap(A[i],A[j]);
		int k=n;
		while(j&(k>>=1))
			j^=k;
		j|=k;
	}
	double pi=flag*acos(0)*2.0;
	for(int i=1;i<n;i<<=1)
	{
		double tmp=pi/i;
		for(int j=0;j<i;j++)
		{
			cpxd w=exp(cpxd(0,tmp*j));
			for(int l=j,r;l<n;l+=(i<<1))
			{
				r=l+i;
				cpxd temp=w*A[r];
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
		}
	}
	if(flag==-1)
		for(int i=0;i<n;i++)
			A[i]/=n;
}
void mul(cpxd *A,cpxd *B,cpxd *C,int n)
{
	int len=1;
	n<<=1;
	while(len<n)len<<=1;
	FFT(A,len,1);
	FFT(B,len,1);
	for(int i=0;i<len;i++)
		C[i]=A[i]*B[i];
	FFT(C,len,-1);
}
cpxd a[MAXN],b[MAXN],ans[MAXN],c[MAXN];
double q[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf",q+i);
	for(int i=1;i<=n;i++)a[i]=cpxd(q[i],0);
	for(int i=1;i<n;i++)b[i+1]=cpxd(1.0/i/i,0);
	mul(a+1,b+1,ans+1,n);
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	for(int i=1;i<=n;i++)a[i]=cpxd(q[n-i+1],0);
	for(int i=1;i<n;i++)b[i+1]=cpxd(1.0/i/i,0);
	mul(a+1,b+1,c+1,n);
	for(int i=1;i<=n;i++)
		ans[i]-=c[n-i+1];
	for(int i=1;i<=n;i++)
		printf("%.3lf\n",ans[i].real());
	return 0;
}
