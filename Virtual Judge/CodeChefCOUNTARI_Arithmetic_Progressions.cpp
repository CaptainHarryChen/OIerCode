#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double PI=acos(-1);
const long long MAXN=100005,MAXL=65540,LEN=65536,BLKSIZ=1000,BLKNUM=MAXN/BLKSIZ;

struct cpx
{
	double r,i;
	cpx(){}
	cpx(double r,double i):r(r),i(i){}
	cpx operator + (const cpx &t)const
	{return cpx(r+t.r,i+t.i);}
	cpx operator - (const cpx &t)const
	{return cpx(r-t.r,i-t.i);}
	cpx operator * (const cpx &t)const
	{return cpx(r*t.r-i*t.i,r*t.i+i*t.r);}
	cpx operator / (double k)const
	{return cpx(r/k,i/k);}
};

void FFT(cpx A[],long long n,long long mode)
{
	for(long long i=0,j=0;i<n;i++)
	{
		if(j>i)
			swap(A[i],A[j]);
		long long k=n>>1;
		while(k&&(k&j))
			j^=k,k>>=1;
		j^=k;
	}
	for(long long i=1;i<n;i<<=1)
		for(long long j=0;j<n;j+=(i<<1))
		{
			cpx w1(cos(PI/i*mode),sin(PI/i*mode)),w(1,0);
			for(long long l=j,r=j+i;l<j+i;l++,r=l+i,w=w*w1)
			{
				cpx temp=A[r]*w;
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
		}
	if(mode==-1)
		for(long long i=0;i<n;i++)
			A[i]=A[i]/n;
}

long long N,A[MAXN];
cpx a[MAXL],b[MAXL];
long long cnt2[MAXL],cntL[MAXL],cntR[MAXL];

long long ans;

int main()
{
	scanf("%lld",&N);
	for(long long i=1;i<=N;i++)
	{
		scanf("%lld",&A[i]);
		cntR[A[i]]++;
	}
	
	ans=0;
	for(long long i=0;i<=N/BLKSIZ;i++)
	{
		long long L=i*BLKSIZ+1,R=min((i+1)*BLKSIZ+1,N+1);
		if(L>N)break;
		for(long long j=L;j<R;j++)
			cnt2[A[j]]++,cntR[A[j]]--;
		
		for(long long x=L;x<R;x++)
			for(long long y=x+1;y<R;y++)
				if(2*A[y]-A[x]>=0)
					ans+=1LL*cntR[2*A[y]-A[x]];
		for(long long y=L;y<R;y++)
			for(long long z=y+1;z<R;z++)
				if(2*A[y]-A[z]>=0)
					ans+=1LL*cntL[2*A[y]-A[z]];
				
		for(long long y=L;y<R;y++)
		{
			cnt2[A[y]]--;
			for(long long x=L;x<y;x++)
				if(2*A[y]-A[x]>=0)
					ans+=1LL*cnt2[2*A[y]-A[x]];
		}
		
		for(long long i=0;i<MAXL;i++)
			a[i]=cpx(cntL[i],0);
		for(long long i=0;i<MAXL;i++)
			b[i]=cpx(cntR[i],0);
		FFT(a,65536,1);
		FFT(b,65536,1);
		for(long long i=0;i<65536;i++)
			a[i]=a[i]*b[i];
		FFT(a,65536,-1);
		
		for(long long y=L;y<R;y++)
			ans+=(long long)(a[2*A[y]].r+0.5);
			
		for(long long j=L;j<R;j++)
			cntL[A[j]]++;
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
