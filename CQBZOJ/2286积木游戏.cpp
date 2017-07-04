#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 10005
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1,a,b=0;i<=n;i++)
	{
		scanf("%d",&a);
		if(a>b)
			ans+=(a-b);
		b=a;
	}
	printf("%d\n",ans);
	return 0;
}
