#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n,a=0,b=0,c;
	cin>>n;
	for(int i=0;i<2*n;i++)
	{
		scanf("%d",&c);
		if(i%2==0)
			a+=c;
		else
			b+=c;
	}
	if(a>b)
		cout<<a<<' '<<b<<endl;
	else
		cout<<b<<' '<<a<<endl;
	return 0;
}
