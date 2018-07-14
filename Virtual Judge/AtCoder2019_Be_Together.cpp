#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=105;

int N;
int a[MAXN];

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	int ans=0x7FFFFFFF;
	for(int s=-100;s<=100;s++)
	{
		int sum=0;
		for(int i=1;i<=N;i++)
			sum+=(s-a[i])*(s-a[i]);
		ans=min(ans,sum);
	}
	printf("%d\n",ans);
	
	return 0;
}
