#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i*2<=n;i++)
		if(n%i==0)
			cout<<i<<endl;
	cout<<n<<endl;
	return 0;
}
