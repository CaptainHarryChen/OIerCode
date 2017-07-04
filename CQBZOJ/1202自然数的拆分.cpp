#include<cstdio>
#include<iostream>
using namespace std;
int n,a[35],k=1;
void f(int m)
{
	if(m==0)
	{
		for(int i=1;i<k-1;i++)
			printf("%d+",a[i]);
        printf("%d\n",a[k-1]);
        return;
	}
	for(int i=m<a[k-1]?m:a[k-1];i>0;i--)
	{
		a[k++]=i;
		f(m-i);
		k--;
		a[k]=0;
	}
}
int main()
{
	cin>>n;
	a[0]=n-1;
	f(n);
	return 0;
}
