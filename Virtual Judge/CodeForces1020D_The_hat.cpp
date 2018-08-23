#include<cstdio>
#include<cstdlib>

int Query(int val)
{
	printf("? %d\n",val);
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}
int finish(int val)
{
	printf("! %d\n",val);
	exit(0);
}

int main()
{
	int n,m;
	scanf("%d",&n);
	m=n/2;
	if(m%2)
		finish(-1);
	int d=Query(1)-Query(m+1);
	if(d==0)
		finish(1);
	int L=2,R=m;
	while(L<=R)
	{
		int mid=(L+R)/2;
		int t=Query(mid)-Query(mid+m);
		if(t==0)
			finish(mid);
		if((t<0&&d<0)||(t>0&&d>0))
			L=mid+1;
		else
			R=mid-1;
	}
	
	finish(-1);
	return 0;
}