#include<cstdio>
const int MAXN=100005;

int n;
int val[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int sum=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&val[i]);
			sum^=val[i];
		}
		for(int i=1;i<n;i++)
			scanf("%*d%*d");
		if(sum==0)
		{
			puts("D");
			continue;
		}
		int bit=(1<<30);
		while((sum&bit)==0)
			bit>>=1;
		bool flag=false;
		for(int i=1;i<=n;i++)
			if(val[i]&bit)
			{
				flag=true;
				break;
			}
		if(flag)
			puts("Q");
		else
			puts("T");
	}
	
	return 0;
}
