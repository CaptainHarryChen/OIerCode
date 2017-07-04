#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
long long T,V,N,s1,v1,s2,v2;
int main()
{
	scanf("%lld",&T);
	for(long long ttt=1;ttt<=T;ttt++)
	{
		V=0;
		scanf("%lld%lld%lld%lld%lld",&N,&s1,&v1,&s2,&v2);
		if(s1>s2)
		{swap(s1,s2);swap(v1,v2);}
		if(N/s2<=65536)
			for(long long j=0;j<=N/s2;j++)
				V=max(V,v2*j+v1*((N-s2*j)/s1));
		else
		{
			for(long long i=0;i<s2;i++)
				V=max(V,v1*i+v2*((N-s1*i)/s2));
			for(long long j=0;j<s1;j++)
				V=max(V,v2*j+v1*((N-s2*j)/s1));
		}
		printf("Case #%lld: %lld\n",ttt,V);
	}
	return 0;
}
