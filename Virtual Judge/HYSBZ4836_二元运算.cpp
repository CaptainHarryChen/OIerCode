#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const double PI=acos(-1);
const int MAXN=200005;

template<class T>
inline void Read(T &x)
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

struct cpx
{
	double r,i;
	cpx(){}
	cpx(double x){r=x;i=0;};
	cpx(double a,double b){r=a;i=b;}
	cpx operator * (const cpx &t)const
	{return cpx(r*t.r-i*t.i,r*t.i+t.r*i);}
	cpx operator / (double t)const
	{return cpx(r/t,i/t);}
	cpx operator + (const cpx &t)const
	{return cpx(r+t.r,i+t.i);}
	cpx operator - (const cpx &t)const
	{return cpx(r-t.r,i-t.i);}
};

void FFT(cpx A[],int len,int mode)
{
	for(int i=0,j=0;i<len;i++)
	{
		if(i<j)swap(A[i],A[j]);
		int k=len>>1;
		while(k&&(k&j))
		{
			j^=k;
			k>>=1;
		}
		j^=k;
	}
	for(int i=1;i<len;i<<=1)
	{
		double ang=2.0*PI*1.0/(i*2.0)*mode;
		cpx w1(cos(ang),sin(ang)),w(1,0);
		for(int j=0;j<i;j++,w=w*w1)
			for(int l=j,r=l+i;l<len;l+=(i<<1),r=l+i)
			{
				cpx temp=A[r]*w;
				A[r]=A[l]-temp;
				A[l]=A[l]+temp;
			}
	}
	if(mode==-1)
		for(int i=0;i<len;i++)
			A[i]=A[i]/len;
}

int n,m,q;
long long ans[MAXN];
int A[MAXN],B[MAXN];
cpx ta[MAXN],tb[MAXN];

void CDQ(int L,int R)
{
	if(L==R)
	{
		ans[0]+=(long long)A[L]*B[L];
		return;
	}
	int mid=(L+R)/2,len=1;
	while(len<=R-L+1)
		len<<=1;
	
	memset(ta,0,sizeof(cpx)*len);
	memset(tb,0,sizeof(cpx)*len);
	for(int i=L;i<=mid;i++)
		ta[i-L]=1.0*A[i];
	for(int i=mid+1;i<=R;i++)
		tb[i-mid-1]=1.0*B[i];
	FFT(ta,len,1);
	FFT(tb,len,1);
	for(int i=0;i<len;i++)
		ta[i]=ta[i]*tb[i];
	FFT(ta,len,-1);
	for(int i=0;i<R-L+1;i++)
		ans[i+L+mid+1]+=(long long)(ta[i].r+0.5);
	
	memset(ta,0,sizeof(cpx)*len);
	memset(tb,0,sizeof(cpx)*len);
	for(int i=mid+1;i<=R;i++)
		ta[i-mid-1]=1.0*A[i];
	for(int i=L;i<=mid;i++)
		tb[mid-i]=1.0*B[i];
	FFT(ta,len,1);
	FFT(tb,len,1);
	for(int i=0;i<len;i++)
		ta[i]=ta[i]*tb[i];
	FFT(ta,len,-1);
	for(int i=0;i<R-L+1;i++)
		ans[i+1]+=(long long)(ta[i].r+0.5);
	
	CDQ(L,mid);
	CDQ(mid+1,R);
}

int main()
{
	int T;
	Read(T);
	while(T--)
	{
		memset(ans,0,sizeof ans);
		memset(A,0,sizeof A);
		memset(B,0,sizeof B);
		Read(n);Read(m);Read(q);
		int mx=0;
		for(int i=1,x;i<=n;i++)
		{
			Read(x);
			A[x]++;
			mx=max(mx,x);
		}
		for(int i=1,x;i<=m;i++)
		{
			Read(x);
			B[x]++;
			mx=max(mx,x);
		}
		CDQ(0,mx);
		for(int i=1,c;i<=q;i++)
		{
			Read(c);
			printf("%lld\n",ans[c]);
		}
	}
	return 0;
}
