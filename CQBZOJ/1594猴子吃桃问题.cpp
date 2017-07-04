#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n=1,y;
	cin>>y;
	for(int i=1;i<y;i++)
	{
		n++;
		n*=2;
	}
	cout<<n<<endl;
}
