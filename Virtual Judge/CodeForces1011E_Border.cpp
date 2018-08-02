#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int n,k;
int a[MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	int g=k;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]%=k;
		g=gcd(a[i],g);
	}
	printf("%d\n",k/g);
	for(int i=0;i<k;i+=g)
		printf("%d ",i);
	
	return 0;
}
