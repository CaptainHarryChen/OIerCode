#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=105;

int a[MAXN];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n/2;i++)
		scanf("%d",a+i);
	sort(a+1,a+n/2+1);
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i+=2)
		ans1+=abs(a[(i+1)/2]-i);
	for(int i=n;i>0;i-=2)
		ans2+=abs(i-a[i/2]);
	printf("%d\n",min(ans1,ans2));
	
	return 0;
}
