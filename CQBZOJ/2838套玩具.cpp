#include<cstdio>
#include<iostream>
#include<fstream>
using namespace std;
int p[1005];
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%d",&p[i]);
	if(n<=3)
	{printf("%d\n",p[0]+p[1]+p[2]);return 0;}
	p[n]=p[0];p[n+1]=p[1];
	int maxp=0,sum;
	for(int i=0;i<n;i++)
	{
		sum=p[i]+p[i+1]+p[i+2];
		if(sum>maxp)
			maxp=sum;
	}
	printf("%d\n",maxp);
	return 0;
}
