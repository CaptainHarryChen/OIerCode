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
	int a,b,x,y,d;
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&a,&b);
		d=exgcd(a,b,x,y);
		a/=d;b/=d;
		int ans=abs(x)+abs(y);
		while(true)
		{
			if(abs(x+b)+abs(y-a)>=ans)
				break;
			x+=b;
			y-=a;
			ans=abs(x)+abs(y);
		}
		while(true)
		{
			if(abs(x-b)+abs(y+a)>=ans)
				break;
			x-=b;
			y+=a;
			ans=abs(x)+abs(y);
		}
		printf("%d %d\n",x,y);
	}
	return 0;
}
