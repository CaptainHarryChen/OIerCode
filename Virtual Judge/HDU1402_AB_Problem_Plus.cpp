#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<complex>
#include<algorithm>
using namespace std;
#define MAXN 200005
typedef complex<double> cpx;
char a[MAXN],b[MAXN];
int ans[MAXN];
void FFT(vector<cpx>&A,bool flag)
{
	int n=A.size();
	for(int i=0,j=0;i<n;i++)
	{
		if(j>i)
			swap(A[i],A[j]);
		int k=n;
		while(j&(k>>=1))
			j&=(~k);
		j|=k;
	}
	double pi=(flag?-1:1)*acos(0)*2.0;
	for(int step=1;step<n;step<<=1)
	{
		double al=pi/step;
		for(int k=0;k<step;k++)
		{
			cpx wk=exp(cpx(0,al*k));
			for(int E=k;E<n;E+=step<<1)
			{
				int O=E+step;
				cpx t=wk*A[O];
				A[O]=A[E]-t;
				A[E]+=t;
			}
		}
	}
	if(flag)
		for(int i=0;i<n;i++)
			A[i]/=n;
}
void trans(char a[],vector<cpx>&X)
{
	for(int i=0;a[i];i++)
		X[i]=cpx(a[i]-'0',0);
}
void multi(char a[],char b[],int ans[],int &len)
{
	int len1=strlen(a)<<1,len2=strlen(b)<<1;
	len=1;
	while(len<max(len1,len2))
		len<<=1;
	vector<cpx>X(len,0);
	vector<cpx>Y(len,0);
	trans(a,X);
	trans(b,Y);
	FFT(X,0);
	FFT(Y,0);
	for(int i=0;i<len;i++)
		X[i]*=Y[i];
	FFT(X,1);
	int over=len=0;
	for(int i=(len1+len2)/2-2;i>=0;i--)
	{
		int t=floor(X[i].real()+over+0.5);
		ans[len++]=t%10;
		over=t/10;
	}
	while(over)
	{
		ans[len++]=over%10;
		over/=10;
	}
	for(len--;len>=0&&ans[len]==0;len--);
	if(len<0)
		len=0;
}
int main()
{
	while(1)
	{
		if(!gets(a))break;
		if(!gets(b))break;
		int len;
		multi(a,b,ans,len);
		for(int i=len;i>=0;i--)
			printf("%d",ans[i]);
		printf("\n");
	}
	return 0;
}
