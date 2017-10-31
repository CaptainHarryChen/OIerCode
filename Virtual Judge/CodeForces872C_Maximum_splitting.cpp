#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n<4||n==5||n==7||n==11)
			puts("-1");
		else
		{
			if(n%2==0)
				printf("%d\n",n/4);
			else
				printf("%d\n",(n-9)/4+1);
		}
	}
	return 0;
}
