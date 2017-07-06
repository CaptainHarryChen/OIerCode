#include<cstdio>
#define MAXN 100005
int w[MAXN],n,k;
int main()
{
	int l=1,r=0,mid,t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",w+i);
		if(r<w[i])
			r=w[i];
	}
	scanf("%d",&k);
	if(k==1)
	{
		printf("%d\n",r);
		return 0;
	}
	while(l<r)
	{
		mid=(l+r)/2;
		t=0;
		for(int i=1;i<=n&&t<=mid;i++)
			if(w[i]>mid)
				t+=(w[i]-mid-1)/(k-1)+1;
		if(t<=mid)
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
