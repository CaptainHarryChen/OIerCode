#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

long long n,h,a,b,k;

int main()
{
	scanf("%I64d%I64d%I64d%I64d%I64d",&n,&h,&a,&b,&k);
	long long ta,fa,tb,fb;
	while(k--)
	{
		scanf("%I64d%I64d%I64d%I64d",&ta,&fa,&tb,&fb);
		if(ta==tb)
		{
			printf("%I64d\n",abs(fa-fb));
			continue;
		}
		long long ans=0;
		if(fa>b)ans+=fa-b,fa=b;
		if(fa<a)ans+=a-fa,fa=a;
		if(fb>b)ans+=fb-b,fb=b;
		if(fb<a)ans+=a-fb,fb=a;
		ans+=abs(ta-tb)+abs(fa-fb);
		printf("%I64d\n",ans);
	}
	
	return 0;
}