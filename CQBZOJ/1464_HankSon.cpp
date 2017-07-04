#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}
int main()
{
	int T,cnt;
	int a0,a1,b0,b1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
		cnt=0;
		for(int x=1;x*x<=b1;x++)
			if(b1%x==0)
			{
				if(x%a1==0&&gcd(x/a1,a0/a1)==1&&gcd(b1/b0,b1/x)==1)
					cnt++;
				int y=b1/x;
				if(y==x)continue;
				if(y%a1==0&&gcd(y/a1,a0/a1)==1&&gcd(b1/b0,b1/y)==1)
					cnt++;
			}
		printf("%d\n",cnt);
	}
	return 0;
}
