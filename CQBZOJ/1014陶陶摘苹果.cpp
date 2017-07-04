#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[10];
int main()
{
	int s,cnt=0;
	for(int i=0;i<10;i++)
		scanf("%d",&a[i]);
	cin>>s;
	for(int i=0;i<10;i++)
		if(a[i]<=s+30)
			cnt++;
	printf("%d\n",cnt);
	return 0;
}
