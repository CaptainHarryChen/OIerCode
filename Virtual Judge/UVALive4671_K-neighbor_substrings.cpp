#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;
const int MAXN=262200;
const double PI=acos(-1);

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

void FFT(cpx A[],int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(j>i)
			swap(A[i],A[j]);
		int k=n>>1;
		while(k&&(k&j))
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
		{
			cpx w1(cos(PI/i*mode),sin(PI/i*mode)),w(1,0);
			for(int l=j,r=j+i;l<j+i;l++,r=l+i,w=w*w1)
			{
				cpx temp=A[r]*w;
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
		}
	if(mode==-1)
		for(int i=0;i<n;i++)
			A[i]=A[i]/n;
}

char sA[MAXN],sB[MAXN];
cpx A[MAXN],B[MAXN];
int len1,len2;
unsigned long long f[MAXN],hash[MAXN];

set<unsigned long long> S;

int main()
{
	int K;
	for(int cas=1;;cas++)
	{
		scanf("%d",&K);
		if(K==-1)
			break;
		scanf("%s%s",sA,sB);
		len1=strlen(sA);
		len2=strlen(sB);
		
		for(int i=0;i<len1;i++)
			A[i]=cpx((sA[i]=='a'?1.0:-1.0),0);
		for(int i=0;i<len2;i++)
			B[i]=cpx((sB[i]=='a'?1.0:-1.0),0);
		reverse(B,B+len2);
		
		int len=1;
		while(len<len1+len2-1)
			len<<=1;
		for(int i=len1;i<len;i++)A[i]=cpx(0,0);
		for(int i=len2;i<len;i++)B[i]=cpx(0,0);
		FFT(A,len,1);
		FFT(B,len,1);
		for(int i=0;i<len;i++)
			A[i]=A[i]*B[i];
		FFT(A,len,-1);
		
		S.clear();
		f[0]=1LLU;
		for(int i=1;i<=len1;i++)
			f[i]=f[i-1]*500009LLU;
		hash[0]=0LLU;
		for(int i=1;i<=len1;i++)
			hash[i]=hash[i-1]*500009LLU+sA[i-1]-'a'+1;
		for(int i=len2-1;i<len1;i++)
			if(len2-(int)(A[i].r+0.5)<=K*2)
				S.insert(hash[i+1]-hash[i-len2+1]*f[len2]);
		printf("Case %d: %d\n",cas,S.size());
	}
	
	return 0;
}
