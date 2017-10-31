#include<cstdio>
#include<cstdlib>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	int x1,y1;
	int d=exgcd(b,a%b,x1,y1);
	x=y1;
	y=x1-a/b*y1;
	return d;
}
int main()
{
	int a,b,c,x,y,d;
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&a,&b,&c);
		d=exgcd(a,b,x,y);
		if(c%d)
			puts("No solution");
		else
		{
			x=x*c/d;
			y=y*c/d;
			printf("%d %d\n",x,y);
		}
	}
	return 0;
}
