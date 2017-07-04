#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,a,b,x,y,d;
void arr(int a,int b)
{
	if(b==0)
	{x=1;y=0;d=a;return;}
	arr(b,a%b);
	int t=x;
	x=y;
	y=t-a/b*y;
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&a,&b);
		arr(b,9973);
		x%=9973;
		while(x<=0)x+=9973;
		long long s=a*x;
		s%=9973;
		printf("%lld\n",s);
	}
	return 0;
}