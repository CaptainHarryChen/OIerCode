#include<cstdio>
int gcd(int a,int b,int &x,int &y)//解ax+by=gcd(a,b)方程，返回最大公约数
{
    if(b==0)
    {x=1;y=0;return a;}
    int g;
    g=gcd(b,a%b,y,x);
    y-=a/b*x;
    return g;
}
int gcd(int a,int b)//最大公约数
{return b==0?a:gcd(b,a%b);}
int main()
{
	freopen("Gcd&exGcd_data.in","r",stdin);
	int a,b;
	scanf("%d%d",&a,&b);
	printf("Gcd:%d\n",gcd(a,b));
	int x,y,g;
	g=gcd(a,b,x,y);
	printf("exGcd:(%d)*(%d)+(%d)*(%d)=%d\n",a,x,b,y,g);
	return 0;
}
