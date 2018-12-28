#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=998244353,ROOT=3;
typedef int Poly[MAXN*3];

int PowMod(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1LL*res*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return res;
}

void NTT(Poly &A,int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=n>>1;
		while(k&j)
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
	{
		int w1=PowMod(ROOT,(MOD-1)/(i<<1));
		if(mode==-1)
			w1=PowMod(w1,MOD-2);
		for(int j=0;j<n;j+=(i<<1))
			for(int l=j,r=j+i,w=1;l<j+i;l++,r++,w=1LL*w*w1%MOD)
			{
				int tmp=1LL*w*A[r]%MOD;
				A[r]=(A[l]-tmp+MOD)%MOD;
				A[l]=(A[l]+tmp)%MOD;
			}
	}
	if(mode==-1)
	{
		int invn=PowMod(n,MOD-2);
		for(int i=0;i<n;i++)
			A[i]=1LL*A[i]*invn%MOD;
	}
}

void Inverse(const Poly &A,Poly &B,int n)
{
	if(n==1)
	{
		B[0]=PowMod(A[0],MOD-2);
		return;
	}
	
	static Poly a;
	Inverse(A,B,(n+1)/2);
	int len=1;
	while(len<(n*2-1))
		len<<=1;
	for(int i=0;i<n;i++)
		a[i]=A[i];
	for(int i=n;i<len;i++)
		a[i]=B[i]=0;
	NTT(a,len,1);NTT(B,len,1);
	for(int i=0;i<len;i++)
		B[i]=1LL*B[i]*((2LL-1LL*a[i]*B[i]%MOD+MOD)%MOD)%MOD;
	NTT(B,len,-1);
	for(int i=n;i<len;i++)
		B[i]=0;
}

int n;
Poly A,B;

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&A[i]);
	Inverse(A,B,n);
	for(int i=0;i<n;i++)
		printf("%d%c",B[i]," \n"[i==n-1]);
	
	return 0;
}
