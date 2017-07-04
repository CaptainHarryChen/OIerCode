#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MAXN 1010
#define INF 1e24
using namespace std;
int n;
double f[MAXN][MAXN];
struct zuobiao
{
	double x,y;
}arr[MAXN];
bool paixu(zuobiao a,zuobiao b)
{
	return a.x<b.x;
}
double dis(zuobiao a,zuobiao b)
{
	double x=a.x-b.x,y=a.y-b.y;
	return sqrt((double)x*x+y*y);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&arr[i].x,&arr[i].y);
	sort(arr+1,arr+n+1,paixu);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=INF;
	f[2][1]=dis(arr[1],arr[2]);
	for(int i=3;i<=n;i++)
		for(int j=1;j<i;j++)
		{
			if(j<i-1)
				f[i][j]=f[i-1][j]+dis(arr[i-1],arr[i]);
			else if(j==i-1)
			{
				for(int k=1;k<i-1;k++)
					f[i][j]=min(f[i][j],f[i-1][k]+dis(arr[k],arr[i]));
			}
		}
	printf("%.2lf\n",f[n][n-1]+dis(arr[n],arr[n-1]));
	return 0;
}
