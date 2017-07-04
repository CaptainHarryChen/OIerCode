#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=n;;i++)
		if((i%3==2)&&(i%5==3)&&(i%7==5))
		{
			cout<<i<<endl;
			break;
		}
	return 0;
}
