#include<cstdio>
#include<cstring>
#include<cmath>
#include<complex>
#include<algorithm>
using std::complex;
using std::swap;
using std::sort;
using std::max;
#define MAXN 200005
typedef complex<double> cpxd;
void FFT(cpxd A[],int n,int flag)
{
	for(int i=0,j=0,k;i<n;i++)
	{
		if(j>i)swap(A[j],A[i]);
		k=n;
		while(j&(k>>=1))
			j^=k;
		j|=k;
	}
	double pi=(double)flag*acos(0.0)*2;
	for(int i=1;i<n;i<<=1)
	{
		double al=pi/i;
		for(int k=0;k<i;k++)
		{
			cpxd wk=exp(cpxd(0,al*k));
			for(int Ek=k;Ek<n;Ek+=i<<1)
			{
				int Ok=Ek+i;
				cpxd t=wk*A[Ok];
				A[Ok]=A[Ek]-t;
				A[Ek]=A[Ek]+t;
			}
		}
	}
	if(flag==-1)
		for(int i=0;i<n;i++)
			A[i]/=n;
}
cpxd cpx[MAXN<<1];
int a[MAXN];
long long sum[MAXN<<1],num[MAXN<<1];
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		memset(sum,0,sizeof sum);
		memset(num,0,sizeof num);
		memset(cpx,0,sizeof cpx);
		memset(a,0,sizeof a);
		scanf("%d",&n);
		int len=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
			num[a[i]]+=1;
			len=max(len,a[i]);
		}
		len++;
		for(int i=0;i<len;i++)
			cpx[i]=num[i];
		len<<=1;
		int digit;
		for(digit=1;digit<len;digit<<=1);
		FFT(cpx,digit,1);
		for(int i=0;i<digit;i++)
			cpx[i]=cpx[i]*cpx[i];
		FFT(cpx,digit,-1);
		for(int i=0;i<len;i++)
			num[i]=(long long)(cpx[i].real()+0.5);
		for(int i=0;i<n;i++)
			num[a[i]+a[i]]-=1LL;
		for(int i=0;i<len;i++)
			num[i]/=2LL;
		for(int i=0;i<len;i++)
			sum[i]=i-1<0?0:sum[i-1]+(long long)(num[i]+0.5);
		long long ans1=0,ans2=0;
		sort(a,a+n);
		for(int i=0;i<n;i++)
		{
			ans1+=sum[len-1]-sum[a[i]];
			ans1-=1LL*(n-1-i)*i;
			ans1-=(n-1);
			ans1-=1LL*(n-1-i)*(n-1-i-1)/2LL;
		}
		ans2=1LL*n*(n-1)*(n-2)/6;
		printf("%.7lf\n",1.0*ans1/ans2);
	}
	return 0;
}