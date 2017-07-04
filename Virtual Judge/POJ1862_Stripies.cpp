#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
priority_queue<double>str;
#define MAXN 105
int N;
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		double m;
		scanf("%lf",&m);
		str.push(m);
	}
	for(int i=1;i<N;i++)
	{
		double a,b,c;
		a=str.top();str.pop();
		b=str.top();str.pop();
		c=2*sqrt(a*b);
		str.push(c);
	}
	printf("%.3lf\n",str.top());
	return 0;
}
