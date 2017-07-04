#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int a,b,c,d,e,f,n,m;
	cin>>a>>b>>c>>d>>e>>f;
	n=a*3600+b*60+c;
	m=d*3600+e*60+f;
	cout<<m-n<<endl;
}
