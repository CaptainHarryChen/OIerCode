#include<cstdio>
#include<iostream>
#include<cstring>
#include<climits>
#include<cmath>
using namespace std;
int n,m,p,A,B,q=1,s[4],t[4],train[105];
double side[405][405],dis[405];
bool used[405];
struct dian
{
	int x,y;
}dot[405];
double quanzhi(int x,int y)
{
	if(x==y)return 0;
	double d=sqrt((dot[x].x-dot[y].x)*(dot[x].x-dot[y].x)+(dot[x].y-dot[y].y)*(dot[x].y-dot[y].y));
	if((int)(x-1)/4==(int)(y-1)/4)
		return d*train[(int)(x-1)/4+1];
	return d*p;
}
int main()
{
	scanf("%d",&n);
	for(;n>0;n--)
	{
		scanf("%d%d%d%d",&m,&p,&A,&B);
		for(int i=1;i<=4*m;i++)
			for(int j=1;j<=4*m;j++)
				side[i][j]=-1;
		for(int i=1;i<=m;i++)
		{
			int x1,y1,x2,y2,x3,y3,x4,y4;
			scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
			scanf("%d",&train[i]);
			if((x1-x2)*(x3-x2)+(y1-y2)*(y3-y2)==0)
			{x4=x1-x2+x3;y4=y1-y2+y3;}
			else if((x1-x3)*(x2-x3)+(y1-y3)*(y2-y3)==0)
			{x4=x2-x3+x1;y4=y2-y3+y1;}
			else
			{x4=x3-x1+x2;y4=y3-y1+y2;}
			dot[q].x=x1;dot[q++].y=y1;
			dot[q].x=x2;dot[q++].y=y2;
			dot[q].x=x3;dot[q++].y=y3;
			dot[q].x=x4;dot[q++].y=y4;
			if(i==A)
			{s[0]=q-4;s[1]=q-3;s[2]=q-2;s[3]=q-3;}
			if(i==B)
			{t[0]=q-4;t[1]=q-3;t[2]=q-2;t[3]=q-3;}
		}
		double mins[4];
		int qq=0;
		mins[0]=mins[1]=mins[2]=mins[3]=9999999;
		double print=10000000;
		for(int i=0;i<4;i++)
		{
			for(int k=1;k<=4*m;k++)
				dis[k]=99999999;
			dis[s[i]]=0;
			memset(used,0,sizeof(used));
			for(int k=1;k<=m*4;k++)
			{
				double mindis=99999999;
				int mindot;
				for(int j=1;j<=4*m;j++)
				{
					if(used[j])
						continue;
					if(mindis>dis[j])
					{mindis=dis[j];mindot=j;}
				}
				used[mindot]=1;
				for(int j=1;j<=4*m;j++)
				{
					if(side[mindot][j]==-1)
						side[mindot][j]=quanzhi(mindot,j);
					if(dis[j]>dis[mindot]+side[mindot][j])
						dis[j]=dis[mindot]+side[mindot][j];
				}
			}
			for(int j=0;j<4;j++)
				if(dis[t[j]]<mins[qq])
					mins[qq]=dis[t[j]];
			qq++;
		}
		for(int j=0;j<4;j++)
			if(print>mins[j])
				print=mins[j];
		printf("%.2lf\n",print);
	}
	return 0;
}
