#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 50007
int n,m;
struct XY{int x,y;}num[MAXN],choose[4];
bool cmp(XY a,XY b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
bool check(int s,int k)
{
	for(int i=m;i>0;i--)
		if(!(s&(1<<(i-1)))&&num[k].x==choose[i].x)
			return 0;
		else if((s&(1<<(i-1)))&&num[k].y==choose[i].y)
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&num[i].x,&num[i].y);
	sort(num+1,num+n+1,cmp);
	bool flag;
	for(int i=0;i<8;i++)
	{
		m=0;
		memset(choose,0,sizeof choose);
		flag=1;
		for(int j=1;j<=n;j++)
			if(check(i,j))
			{
				if(m>=3)
				{
					flag=0;
					break;
				}
				else
				{
					m++;
					choose[m].x=num[j].x;
					choose[m].y=num[j].y;
				}
			}
		if(flag)
		{printf("1\n");return 0;}
	}
	printf("0\n");
	return 0;
}
