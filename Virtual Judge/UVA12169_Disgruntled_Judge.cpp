#include<cstdio>
const int MAXN=10005,MOD=10001;

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
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	int xx,yy,g=exgcd(b,a%b,xx,yy);
	x=yy;
	y=xx-(a/b)*yy;
	return g;
}

int n,A[MAXN],B[MAXN];

int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		if(n<2)
		{
			for(int i=1;i<=n;i++)
				printf("0\n");
			continue;
		}
		for(int a=1;a<MOD;a++)
		{
			int tmp=(A[2]-1LL*a*a%MOD*A[1]%MOD)%MOD,b;
			tmp=(tmp+MOD)%MOD;
			if(a==MOD-1)
			{
				if(tmp==0)
					b=0;
				else
					continue;
			}
			else
			{
				int q,g;
				g=exgcd(a+1,MOD,b,q);
				if(tmp%g!=0)
					continue;
				b=(b%MOD+MOD)%MOD;
				b=(1LL*b*(tmp/g))%MOD;
			}
			//if(a==1)
			//	printf("(a,b):(%d,%d)\n",a,b);
			//if(A[2]!=((1LL*a*a%MOD*A[1]%MOD+1LL*a*b%MOD+b)%MOD))
			//	printf("ERROR!\n");
			bool flag=true;
			for(int j=1;j<=n;j++)
			{
				B[j]=(1LL*A[j]*a+b)%MOD;
				if(j<n&&(1LL*B[j]*a+b)%MOD!=A[j+1])
				{
					flag=false;
					break;
				}
			}
			if(flag)
				break;
		}
		for(int i=1;i<=n;i++)
			printf("%d\n",B[i]);
	}
	return 0;
}
