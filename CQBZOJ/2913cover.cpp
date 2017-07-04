#include<cstdio>
#include<iostream>
#include<cstring>
#define INF 2139062143
using namespace std;
int n,x,y,minx=INF,miny=INF,maxx,maxy,maxside;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		minx=min(minx,x);
		miny=min(miny,y);
		maxx=max(maxx,x);
		maxy=max(maxy,y);
	}
	maxside=maxx-minx;
	maxside=max(maxside,maxy-miny);
	printf("%d\n",maxside*maxside);
	return 0;
}
