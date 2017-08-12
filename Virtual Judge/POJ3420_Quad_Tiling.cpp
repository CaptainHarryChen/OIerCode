#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=20;
struct Matrix
{
	static int MOD;
	int h,w,a[MAXN][MAXN];
	Matrix(){h=w=0;}
	Matrix(int h,int w):h(h),w(w)
	{
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
				a[i][j]=0;
	}
	Matrix operator * (const Matrix &t)const
	{
		Matrix res(0,0);
		int l=t.h;
		if(l!=this->w)
			return res;
		int h=this->h;
		int w=t.w;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
				for(int k=0;k<l;k++)
					res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%MOD)%MOD;
		return res;
	}
	Matrix pow(int b)const
	{
		Matrix res(0,0);
		if(h!=w)
			return res;
		Matrix d=*this;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			res.a[i][i]=1;
		while(b)
		{
			if(b&1)
				res=res*d;
			d=d*d;
			b>>=1;
		}
		return res;
	}
};
int Matrix::MOD;
int main()
{
	Matrix A(16,16);
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
		{
			A.a[i][j]=1;
			int x=i&j;
			if(x==1||x==2||x==4||x==5||x==7||x==8||x==9||x==10||x==11||x==13||x==14)
				A.a[i][j]=0;
			for(int k=1;k<16;k<<=1)
				if((i&k)==0&&(j&k)==0)
				{
					A.a[i][j]=0;
					break;
				}
		}
	Matrix B(16,1);
	int N;
	while(true)
	{
		scanf("%d%d",&N,&Matrix::MOD);
		if(!N&&!Matrix::MOD)
			break;
		for(int i=0;i<16;i++)
			B.a[i][0]=A.a[15][i];
		B=A.pow(N-1)*B;
		printf("%d\n",B.a[15][0]);
	}
	return 0;
}
