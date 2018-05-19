#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n,k;
int a[MAXN],mn[MAXN],mx[MAXN];
int q[MAXN],hd,tl;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	
	mn[1]=a[1];
	q[hd=tl=1]=1;
	for(int i=2;i<=n;i++)
	{
		while(hd<=tl&&a[q[tl]]>=a[i])
			tl--;
		while(hd<=tl&&i-q[hd]>=k)
			hd++;
		mn[i]=hd>tl?a[i]:a[q[hd]];
		q[++tl]=i;
	}
	mx[1]=a[1];
	q[hd=tl=1]=1;
	for(int i=2;i<=n;i++)
	{
		while(hd<=tl&&a[q[tl]]<=a[i])
			tl--;
		while(hd<=tl&&i-q[hd]>=k)
			hd++;
		mx[i]=hd>tl?a[i]:a[q[hd]];
		q[++tl]=i;
	}
	for(int i=k;i<n;i++)
		printf("%d ",mn[i]);
	printf("%d\n",mn[n]);
	for(int i=k;i<n;i++)
		printf("%d ",mx[i]);
	printf("%d\n",mx[n]);
	
	return 0;
}
