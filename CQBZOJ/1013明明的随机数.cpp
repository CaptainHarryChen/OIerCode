#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[105];
bool f[1005];
int main()
{
	int n;
	cin>>n;
	int s=n;
	for(int i=0;i<s;i++)
	{
		scanf("%d",&a[i]);
		if(f[a[i]]){i--;s--;continue;}
		f[a[i]]=1;
	}
	sort(a,a+s);
	printf("%d\n",s);
	for(int i=0;i<s-1;i++)
		printf("%d ",a[i]);
	printf("%d\n",a[s-1]);
	return 0;
}
