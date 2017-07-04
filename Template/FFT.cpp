#include<cstdio>
#include<cmath>
#include<complex>
using namespace std;
const int MAXN=1005;
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
int main()
{
	freopen("FFT_data.in","r",stdin);
	int n;
	scanf("%d",&n);
	cpxd a[MAXN],b[MAXN],c[MAXN];
	double x;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&x);
		a[i]=cpxd(x,0.0);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&x);
		b[i]=cpxd(x,0.0);
	}
	mul(a+1,b+1,c+1,n);
	for(int i=1;i<2*n-1;i++)
		printf("%lf ",c[i].real());
	printf("%lf\n",c[2*n-1].real());
	return 0;
}
