#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 1005
#define ESP 1e-6
int n,d;
struct island
{
	int x,y;
	double s,e;
	bool operator < (const island &t)const
	{return e<t.e||(e==t.e&&s<t.s);}
}isl[MAXN];
int main()
{
	for(int cas=1;;cas++)
	{
		scanf("%d%d",&n,&d);
		if(n==0&&d==0.0)
			break;
		for(int i=1;i<=n;i++)
			scanf("%d%d",&isl[i].x,&isl[i].y);
		printf("Case %d: ",cas);
		bool fail=0;
		for(int i=1;i<=n;i++)
		{
			if(isl[i].y>d)
			{fail=1;break;}
			double a=sqrt(d*d-isl[i].y*isl[i].y);
			isl[i].s=isl[i].x-a;isl[i].e=isl[i].x+a;
		}
		if(fail)
			printf("-1\n");
		else
		{
			sort(isl+1,isl+n+1);
			int ans=0,now=1,j;
			while(now<=n)
			{
				for(j=now+1;j<=n;j++)
					if(isl[now].e<isl[j].s)
					{j--;break;}
				ans++;
				now=j+1;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
