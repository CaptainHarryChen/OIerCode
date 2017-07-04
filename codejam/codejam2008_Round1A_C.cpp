#include<cstdio>
#include<vector>
using namespace std;
typedef vector<int> Vector;
typedef vector<Vector> Matrix;
Matrix operator * (Matrix a,Matrix b)
{
	int as1=a.size(),as2=a[0].size(),bs1=b.size(),bs2=b[0].size();
	if(as2!=bs1)
		return Matrix(0,Vector(0));
	Matrix ret(as2,Vector(bs1,0));
	for(int i=0;i<as1;i++)
		for(int j=0;j<bs2;j++)
			for(int k=0;k<as2;k++)
				ret[i][j]=(ret[i][j]+(a[i][k]*b[k][j])%1000)%1000;
	return ret;
}
Matrix pow(Matrix a,int b)
{
	Matrix c(a.size(),Vector(a.size(),0));
	for(int i=0;i<(int)a.size();i++)
		c[i][i]=1;		
	for(;b;b>>=1,a=a*a)
		if(b&1)
			c=c*a;
	return c;
}
namespace SolutionA
{
	int solve(int n)
	{
		Matrix a(2,Vector(2,0));
		a[0][0]=3;a[0][1]=5;
		a[1][0]=1;a[1][1]=3;
		a=pow(a,n);
		return (a[0][0]*2+999)%1000;
	}
}
namespace SolutionB
{
	int solve(int n)
	{
		Matrix b(2,Vector(2));
		b[0][0]=6;b[0][1]=-4;
		b[1][0]=1;b[1][1]=0;
		b=pow(b,n);
		int ret=b[1][0]*6+b[1][1]*2+999;
		while(ret<0)
			ret+=1000;
		return ret%1000;
	}
}
namespace SolutionC
{
	int solve(int n)
	{
		if(n>103)
			n=(n-3)%100+3;
		return SolutionB::solve(n);
	}
}
int main()
{
	int T,n;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&n);
		//printf("Case #%d: %03d\n",i,SolutionA::solve(n));
		//printf("Case #%d: %03d\n",i,SolutionB::solve(n));
		printf("Case #%d: %03d\n",i,SolutionC::solve(n));
	}
	return 0;
}
