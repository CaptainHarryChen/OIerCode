#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 2000000000
using namespace std;
void solve(int n)
{
	int a,b,c,Max=0;
	for(a=n;a>=0;a--)
		for(b=n;b>=0;b--)
		{
			if((a+b)%2!=0){continue;}
			for(c=n;c>=0;c--)
			{
				if((b+c)%3!=0){continue;}
				if((a+b+c)%5!=0){continue;}
				Max=max(Max,a+b+c);
			}
			b-=2;
		}
	printf("%d\n",Max);
}
int main()
{
	int n,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		solve(n);
	}
	return 0;
}
