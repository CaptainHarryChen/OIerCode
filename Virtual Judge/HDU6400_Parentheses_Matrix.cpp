#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=205;

int main()
{
	int T,n,m;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(n%2==1)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
					putchar('('+((j&1)^1));
				puts("");
			}
			continue;
		}
		if(m%2==1)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
					putchar('('+((i&1)^1));
				puts("");
			}
			continue;
		}
		if(min(n,m)<=4)
		{
			if(n>m)
			{
				for(int i=1;i<=n;i++)
				{
					if(i&1)
						for(int j=1;j<=m;j++)
							putchar('('+((j&1)^1));
					else
					{
						putchar('(');
						for(int j=2;j<m;j++)
							putchar('('+(j&1));
						putchar(')');
					}
					puts("");
				}
			}
			else
			{
				for(int i=1;i<=n;i++)
				{
					if(i==1||i==n)
						for(int j=1;j<=m;j++)
							putchar('('+(i==n));
					else
						for(int j=1;j<=m;j++)
							putchar('('+((i+j)&1));
					puts("");
				}
			}
		}
		else
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
				{
					if(i==1)
						putchar('(');
					else if(i==n)
						putchar(')');
					else if(j==1)
						putchar('(');
					else if(j==m)
						putchar(')');
					else
						putchar('('+((i+j)&1));
				}
				puts("");
			}
		}
	}
	
	return 0;
}
