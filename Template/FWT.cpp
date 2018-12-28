#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=(1<<20)+10,MOD=1000000007,INV2=(MOD+1)/2;

template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}
template<class T>
void Put(T &x)
{
	static char buf[20];
	int len=0;
	do
		buf[len++]=x%10+'0',x/=10;
	while(x);
	while(len)
		putchar(buf[--len]);
}

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=1LL*ret*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return ret;
}

void FWT(int A[],int n,int mode)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
		{
			for(int l=j,r=l+i;l<j+i;l++,r++)
			{
				int a=A[l],b=A[r];
				A[l]=(a+b)%MOD;
				A[r]=(a-b+MOD)%MOD;
				if(mode==-1)
					A[l]=1LL*A[l]*INV2%MOD,A[r]=1LL*A[r]*INV2%MOD;
			}
		}
}

int n,t,A[MAXN],B[MAXN];

int main()
{
	Read(n);Read(t);
	for(int i=0;i<(1<<n);i++)
		Read(B[i]);
	A[0]=1;
	for(int i=0;i<n;i++)
		A[(1<<i)]=1;
	FWT(A,1<<n,1);
	FWT(B,1<<n,1);
	for(int i=0;i<(1<<n);i++)
		B[i]=1LL*B[i]*PowMod(A[i],t)%MOD;
	FWT(B,1<<n,-1);
	for(int i=0;i<(1<<n);i++)
		Put(B[i]),putchar(" \n"[i==(1<<n)-1]);
	
	return 0;
}
