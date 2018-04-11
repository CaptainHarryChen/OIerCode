#include<cstdio>
const int MAXN=20005,MAXV=30001;

int ans[MAXN];
bool used[MAXV];
int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}

int main()
{
	int n,sum=0,i,j;
	scanf("%d",&n);
	for(i=1,j=1;j<n;i++)
		if(i%2==0||i%3==0)
		{
			ans[j++]=i;
			used[i]=true;
			sum+=i;
		}
	int r2=(sum-2)%2,r3=(sum-3)%3;
	for(i=1;j<=n;i++)
		if(!used[i]&&(i+r2)%2==0&&(i+r3)%3==0&&gcd(i,sum)!=1)
			ans[j++]=i;
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	
	return 0;
}
