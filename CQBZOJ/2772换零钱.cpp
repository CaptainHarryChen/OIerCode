#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int n,a,b,c,count=0;
	cin>>n;
	for(a=1;a<=n*100;a++)
		for(b=1;b<=n*50;b++)
			for(c=1;c<=n*20;c++)
				if(a*1+b*2+c*5==n*100)
					count++;
	cout<<count<<endl;
	return 0;
}
