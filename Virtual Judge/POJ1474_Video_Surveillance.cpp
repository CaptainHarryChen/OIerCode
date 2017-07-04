#include<cstdio>
#define MAXN 105
#define INF 0x7FFFFFFF
#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)
typedef struct Vector
{
	int x,y;
	Vector(){}
	void Read()
	{scanf("%d%d",&x,&y);}
}Point;
Point P[MAXN];
int main()
{
	int n,test=0;
	while(~scanf("%d",&n)&&n)
	{
		test++;
		for(int i=n;i>0;i--)
			P[i].Read();
		P[0]=P[n];
		int mn_x=-INF,mx_x=INF,mn_y=-INF,mx_y=INF;
		for(int i=0;i<n;i++)
			if(P[i].x==P[i+1].x)
			{
				if(P[i].y>P[i+1].y)
					mn_x=max(mn_x,P[i].x);
				else
					mx_x=min(mx_x,P[i].x);
			}
			else
			{
				if(P[i].x<P[i+1].x)
					mn_y=max(mn_y,P[i].y);
				else
					mx_y=min(mx_y,P[i].y);
			}
		if(test>1)printf("\n");
		if(mn_x<=mx_x&&mn_y<=mx_y)
			printf("Floor #%d\nSurveillance is possible.\n",test);
		else
			printf("Floor #%d\nSurveillance is impossible.\n",test);
	}
	return 0;
}
