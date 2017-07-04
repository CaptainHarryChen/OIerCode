#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;
struct dian
{
	int x,y;
}dian[105];
double bian[105][105],dis[105];
int n,m,s,t;
bool used[105];
double juli(int x,int y)
{
	int a=dian[x].x-dian[y].x,b=dian[x].y-dian[y].y;
	a=a<0?-a:a;
	b=b<0?-b:b;
	return sqrt(a*a+b*b);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%d%d",&dian[i].x,&dian[i].y);
	cin>>m;
	int a,b;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		bian[a-1][b-1]=juli(a-1,b-1);
		bian[b-1][a-1]=bian[a-1][b-1];
	}
	cin>>s>>t;
	memset(dis,127,sizeof(dis));
	dis[s-1]=0;
	for(int i=0;i<n;i++)
	{
		int k,min=INT_MAX;
		for(int j=0;j<n;j++)
			if(used[j]==0&&dis[j]<min)
			{min=dis[j];k=j;}
		for(int j=0;j<n;j++)
			if(bian[k][j]&&dis[j]>dis[k]+bian[k][j])
				dis[j]=dis[k]+bian[k][j];
		used[k]=1;
	}
	printf("%.2lf\n",dis[t-1]);
	return 0;
}
