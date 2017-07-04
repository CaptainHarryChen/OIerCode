#include<cstdio>
int a[2000000],b[2000000];
int main()
{
	int T,n,k;
	scanf("%d",&T);
	for(int test=1;test<=T;test++)
	{
		scanf("%d%d",&n,&k);
		int i=0,j=0;
		a[0]=b[0]=1;
		while(a[i]<n)
		{
			i++;
			a[i]=b[i-1]+1;
			while(a[j+1]*k<a[i])
				j++;
			if(a[j]*k<a[i])
				b[i]=b[j]+a[i];
			else
				b[i]=a[i];
		}
		printf("Case %d: ",test);
		if(a[i]==n)
			printf("lose\n");
		else
		{
			int ans;
			while(n)
			{
				if(n>=a[i])
				{
					n-=a[i];
					ans=a[i];
				}
				i--;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
