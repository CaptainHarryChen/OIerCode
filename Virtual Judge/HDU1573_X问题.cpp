#include<cstdio>
const int MAXM=13;
long long gcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	long long xx,yy,d=gcd(b,a%b,xx,yy);
	x=yy;
	y=xx-a/b*yy;
	return d;
}
long long a[MAXM],b[MAXM];
int main()
{
	int T,M;
	long long N,A,B,d,l,x,y,p,q,r;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%I64d%d",&N,&M);
		for(int i=1;i<=M;i++)
			scanf("%I64d",a+i);
		for(int i=1;i<=M;i++)
			scanf("%I64d",b+i);
		A=a[1];B=b[1];
		bool flag=true;
		for(int i=2;i<=M;i++)
		{
			p=A;q=a[i];r=b[i]-B;
			d=gcd(p,q,x,y);
			if(r%d)
			{flag=false;break;}
			p/=d;q/=d;r/=d;
			x=x*r;
			x=(x%q+q)%q;
			l=A/d*a[i];
			B=x*A+B;
			B=(B%l+l)%l;
			A=l;
			if(B>N)break;
		}
		if(flag&&B<=N)
			printf("%I64d\n",(N-B)/A+(B!=0));
		else
			puts("0");
	}
	return 0;
}
