#include<cstdio>
#include<cstring>
const int MAXN=100005;

int main()
{
	int n,m,x,d;
	scanf("%d%d",&n,&m);
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&d);
		ans+=1LL*x*n;
		if(d<0)
			ans+=((1LL*d*(n/2)+1LL*d)*(n/2)-(n%2==0?(1LL*d*(n/2)):0));
		else
			ans+=1LL*d*(n-1)*n/2LL;
	}
	printf("%.10lf\n",1.0*ans/n);
	
	return 0;
}
