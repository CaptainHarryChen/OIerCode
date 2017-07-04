#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int n;
	cin>>n;
	bool f=1;
	if(n==2){cout<<"FALSE"<<endl;return 0;}
	for(int i=2;i<=n/2;i++)
		if(n%i==0)
		{f=0;break;}
	if(f)
		cout<<"TRUE"<<endl;
	else
		cout<<"FALSE"<<endl;
	return 0;
}
