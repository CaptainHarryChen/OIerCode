#include<cstdio>
#include<cstdlib>
const int MAXN=35;

int p[MAXN];

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
	{
		printf("1\n");
		fflush(stdout);
		scanf("%d",&p[i]);
		if(p[i]==0)
			exit(0);
	}
	int L=1,R=m,cnt=1;
	while(L<R)
	{
		int mid=(L+R)/2;
		printf("%d\n",mid);
		fflush(stdout);
		int t;
		scanf("%d",&t);
		if(t==0)
			exit(0);
		t*=p[cnt];
		cnt=cnt%n+1;
		if(t==1)
			L=mid+1;
		else
			R=mid-1;
	}
	printf("%d\n",L);
	fflush(stdout);
	
	return 0;
}
