#include<cstdio>
#include<cmath>
#include<complex>
using namespace std;
const double PI=acos(-1);
const int MAXN=40005,MAXS=140000,ZERO=20000;
typedef complex<double> cpx;

void FFT(cpx A[],int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=n>>1;
		while(k&&(k&j))
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
	{
		for(int j=0;j<n;j+=(i<<1))
		{
			cpx w1=cpx(cos(mode*PI/i),sin(mode*PI/i)),w(1,0);
			for(int l=j,r=j+i;l<j+i;l++,r++,w=w*w1)
			{
				cpx temp=A[r]*w;
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
		}
	}
	if(mode==-1)
		for(int i=0;i<n;i++)
			A[i]/=n;
}

void mul(const int A[],int len1,const int B[],int len2,int C[])
{
	static cpx cA[MAXS],cB[MAXS];
	int len=1;
	while(len<len1+len2-1)
		len<<=1;
	for(int i=0;i<len1;i++)cA[i]=A[i];
	for(int i=len1;i<len;i++)cA[i]=0;
	for(int i=0;i<len2;i++)cB[i]=B[i];
	for(int i=len2;i<len;i++)cB[i]=0;
	FFT(cA,len,1);FFT(cB,len,1);
	for(int i=0;i<len;i++)
		cA[i]*=cB[i];
	FFT(cA,len,-1);
	for(int i=0;i<len;i++)
		C[i]=(int)(cA[i].real()+0.5);
}

int f1[MAXS],f2[MAXS],f3[MAXS];
int t1[MAXS],t2[MAXS];
int ans[MAXS];

int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1,a;i<=N;i++)
	{
		scanf("%d",&a);
		f1[a+ZERO]++;
		f2[a*2+ZERO*2]++;
		f3[a*3+ZERO*3]++;
	}
	mul(f1,ZERO*2+1,f1,ZERO*2+1,t1);
	mul(t1,ZERO*4+1,f1,ZERO*2+1,t1);
	mul(f1,ZERO*2+1,f2,ZERO*4+1,t2);

	for(int i=0;i<ZERO*6+1;i++)
		ans[i]=(t1[i]-3*t2[i]+2*f3[i])/6;
	
	for(int i=0;i<MAXS;i++)
		if(ans[i])
			printf("%d : %d\n",i-ZERO*3,ans[i]);
	
	return 0;
}
