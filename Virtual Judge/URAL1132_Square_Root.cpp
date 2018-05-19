#include<cstdio>
#include<cstdlib>

int n,W,P;

struct Complex
{
	int r,i;
	Complex operator * (const Complex &t)const
	{
		Complex res;
		res.r=(t.r*r%P+t.i*i%P*W%P)%P;
		res.i=(t.r*i%P+t.i*r%P)%P;
		return res;
	}
};

Complex pow(Complex x,int y)
{
	Complex res;
	res.r=1;res.i=0;
	while(y)
	{
		if(y&1)
			res=x*res;
		x=x*x;
		y>>=1;
	}
	return res;
}
int pow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
			res=(x*res)%P;
		x=(x*x)%P;
		y>>=1;
	}
	return res;
}

int main()
{
	int T,a;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&P);
		n%=P;
		if(P==2)
		{
			printf("%d\n",n);
			continue;
		}
		if(pow(n,(P-1)/2)==P-1)
		{
			puts("No root");
			continue;
		}
		for(;;)
		{
			a=rand();
			if(pow((a*a%P-n+P)%P,(P-1)/2)==P-1)
				break;
		}
		W=(a*a%P-n+P)%P;
		Complex res;
		res.r=a;res.i=1;
		res=pow(res,(P+1)/2);
		int x1=res.r,x2=P-res.r;
		if(x1>x2)
			x1^=x2,x2^=x1,x1^=x2;
		if(x1==x2)
			printf("%d\n",x1);
		else
			printf("%d %d\n",x1,x2);
	}
	
	return 0;
}
