#include<cstdio>
#include<algorithm>
using namespace std;
int a[15],t[15];
int n,sum;
int main()
{
	scanf("%d%d",&n,&sum);
	a[0]=1;
	for(int i=1,j=n-1;i<n;i++,j--)
		a[i]=a[i-1]*j/i;
	for(int i=1;i<=n;i++)
		t[i]=i;
	int tsum=0;
	do
	{
		tsum=0;
		for(int i=1;i<=n;i++)
			tsum+=t[i]*a[i-1];
		if(tsum==sum)
		{
			for(int i=1;i<n;i++)
				printf("%d ",t[i]);
			printf("%d\n",t[n]);
			break;
		}
	}while(next_permutation(t+1,t+n+1));
	return 0;
}
