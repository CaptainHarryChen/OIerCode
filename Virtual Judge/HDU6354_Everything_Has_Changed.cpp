#include<cstdio>
#include<cmath>
const double EPS=1e-8;
int dcmp(double a,double b)
{
	if(fabs(a-b)<=EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}

int m,R;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&m,&R);
		double ans=2.0*R*acos(-1);
		for(int i=1;i<=m;i++)
		{
			int x,y,r;
			scanf("%d%d%d",&x,&y,&r);
			double dis=sqrt(x*x+y*y);
			if((dcmp(dis,R)!=-1&&dcmp(dis-r,R)!=1&&dcmp(dis-r,-R)!=-1)
				||(dcmp(dis,R)==-1&&dcmp(dis+r,R)!=-1))
			{
				double a1,a2;
				a1=acos((dis*dis+R*R-r*r)/(2.0*dis*R))*2.0;
				a2=acos((dis*dis+r*r-R*R)/(2.0*dis*r))*2.0;
				ans=ans-a1*R+a2*r;
			}
		}
		printf("%.10lf\n",ans);
	}
	return 0;
}
