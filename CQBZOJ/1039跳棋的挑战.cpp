#include<cstdio>
#include<iostream>
using namespace std;
int n,cnt,ans[15];
bool b[15],c[30],d[30];
void f(int z)
{
	if(z>=n)
	{
		cnt++;
		if(cnt>=1&&cnt<=3)
		{
			for(int i=0;i<n-1;i++)
				printf("%d ",ans[i]+1);
			printf("%d\n",ans[n-1]+1);
		}
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(b[i]||c[z-i+n]||d[z+i])continue;
		ans[z]=i;
		b[i]=c[z-i+n]=d[z+i]=1;
		f(z+1);
		ans[z]=0;
		b[i]=c[z-i+n]=d[z+i]=0;
	}
}
int main()
{
	scanf("%d",&n);
	f(0);
	printf("%d\n",cnt);
	return 0;
}
