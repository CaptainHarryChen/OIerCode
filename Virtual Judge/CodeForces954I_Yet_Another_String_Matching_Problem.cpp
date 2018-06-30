#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double PI=acos(-1);
const int MAXN=125005,MAXL=262200;

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


char S[MAXN],T[MAXN];
bool dp[6][6][MAXN];
int ans[MAXN];
cpx A[MAXL],B[MAXL];
int t[MAXL];

int fa[10];
int Find(int a)
{return fa[a]==-1?a:(fa[a]=Find(fa[a]));}

int main()
{
	scanf("%s%s",S,T);
	int len1=strlen(S),len2=strlen(T);
	int len=1;
	while(len<len1+len2-1)
		len<<=1;
	for(int c1=0;c1<6;c1++)
		for(int c2=0;c2<6;c2++)
		{
			memset(A,0,sizeof(cpx)*len);
			for(int i=0;i<len1;i++)
				A[i].r=(S[i]==c1+'a');
			memset(B,0,sizeof(cpx)*len);
			for(int i=0;i<len2;i++)
				B[len2-i-1].r=(T[i]==c2+'a');
			FFT(A,len,1);
			FFT(B,len,1);
			for(int i=0;i<len;i++)
				A[i]=A[i]*B[i];
			FFT(A,len,-1);
			for(int i=len2-1;i<len1;i++)
				dp[c1][c2][i-len2+1]=((int)(A[i].r+0.5)!=0);
		}
	for(int i=0;i<len1-len2+1;i++)
	{
		memset(fa,-1,sizeof fa);
		for(int c1=0;c1<6;c1++)
			for(int c2=0;c2<6;c2++)
				if(dp[c1][c2][i]&&Find(c1)!=Find(c2))
				{
					ans[i]++;
					fa[Find(c1)]=Find(c2);
				}
	}
	for(int i=0;i<len1-len2+1;i++)
		printf("%d ",ans[i]);
	puts("");
	
	return 0;
}
