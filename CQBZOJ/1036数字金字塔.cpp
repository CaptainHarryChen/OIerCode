#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int arr[1005][1005],f[1005][1005],n;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
		{
			scanf("%d",&arr[i][j]);
			f[0][0]=arr[0][0];
			if(i!=0)
			{
				int a=f[i-1][j]+arr[i][j],b=f[i-1][j-1]+arr[i][j];
				f[i][j]=a>b?a:b;
			}
		}
	int max=0;
	for(int i=0;i<n;i++)
		if(f[n-1][i]>max)
			max=f[n-1][i];
	cout<<max<<endl;
	return 0;
}
