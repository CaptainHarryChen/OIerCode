#include<cstdio>
int main()
{
	long long n,x;
	bool flag;
	while(~scanf("%I64d",&n))
	{
		x=n-1;
		flag=1;
		while(x>=1ll)
		{
			if(flag)
			{
				x++;
				if(x%9ll)x/=9ll;
				else x=x/9ll-1ll;
			}
			else
			{
				x/=2ll;
			}
			flag^=1;
		}
		if(flag)
			printf("Ollie wins.\n");
		else
			printf("Stan wins.\n");
	}
	return 0;
}
