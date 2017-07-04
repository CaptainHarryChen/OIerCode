#include<cstdio>
#include<iostream>
using namespace std;
bool f[25];
int n,r,a[25],cnt;
void ff(int b,int c)
{
	if(b>r)
	{
		for(int i=1;i<b-1;i++)
			printf("%d ",a[i]);
		printf("%d\n",a[b-1]);
		return;
	}
	for(int i=c;i<=n;i++)
    {
        if(f[i]==0)
        {
			a[b]=i;
			f[i]=1;
			ff(b+1,i+1);
			a[b]=0;
			f[i]=0;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&r);
	long long s=1;
	for(int i=n,j=1;j<=r;j++,i--)
		s*=i;
	for(int i=r;i>0;i--)
		s/=i;
	printf("%lld\n",s);
	ff(1,1);
	return 0;
}
