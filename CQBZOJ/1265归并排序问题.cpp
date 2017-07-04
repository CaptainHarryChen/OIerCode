#include<cstdio>
#include<iostream>
using namespace std;
int n,a[100000];
void sort_(int x,int y)
{
	int mid=a[(x+y)/2];
	int i=x,j=y;
	while(j>=i)
	{
		while(a[i]<mid)i++;
		while(a[j]>mid)j--;
		if(j>=i)
		{
			swap(a[i],a[j]);
			i++;
			j--;
		}
	}
	if(x<j)sort_(x,j); 
	if(y>i)sort_(i,y);
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort_(0,n-1);
	for(int i=0;i<n-1;i++)
		printf("%d ",a[i]);
	printf("%d",a[n-1]);
	return 0;
}
