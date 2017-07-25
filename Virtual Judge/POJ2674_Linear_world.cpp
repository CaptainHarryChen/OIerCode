#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=32005;
int N;
double L,V;
struct People
{
	char name[256];
	int dir;
	double pos;
}pe[MAXN];
int main()
{
	char dd[5];
	while(1)
	{
		scanf("%d",&N);
		if(!N)break;
		scanf("%lf%lf",&L,&V);
		double mx=0.0;
		int id;
		for(int i=1;i<=N;i++)
		{
			scanf("%s%lf%s",dd,&pe[i].pos,pe[i].name);
			if(dd[0]=='p'||dd[0]=='P')
			{
				pe[i].dir=1;
				if((L-pe[i].pos)/V>mx)
				{
					mx=(L-pe[i].pos)/V;
					id=i;
				}
			}
			else
			{
				pe[i].dir=-1;
				if(pe[i].pos/V>mx)
				{
					mx=pe[i].pos/V;
					id=i;
				}
			}
		}
		printf("%13.2lf ",((int)(mx*100))/100.0);
		int cnt=0;
		for(int i=id+pe[id].dir;i>0&&i<=N;i+=pe[id].dir)
			cnt+=(pe[i].dir!=pe[id].dir);
		printf("%s\n",pe[id+cnt*pe[id].dir].name);
	}
	return 0;
}
