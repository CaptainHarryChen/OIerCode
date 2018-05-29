#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int N,P,Q;

int main()
{
	scanf("%d%d%d",&P,&Q,&N);
	double ans=0;
	for(int i=1;i<=N;i++)
	{
		double t=1,e=0;
		int nowp=P,step=1;
		for(step=1;nowp<100;step++)
		{
			e+=t*nowp*step/100.0;
			t*=1-nowp/100.0;
			nowp+=Q;
		}
		e+=t*step;
		P/=2;
		ans+=e;
	}
	
	printf("%.2lf\n",ans);
	
	return 0;
}
