#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
bool m[1000001];
int main()
{
	int n;
	cin>>n;
	m[1]=1;
	for(int i=1,j=0;j<n;i++)
	{
		if(m[i]==1)
		{
			m[2*i+1]=1;
			m[3*i+1]=1;
			printf("%d\n",i);
			j++;
		}
	}
	return 0;
}
