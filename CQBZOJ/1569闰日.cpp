#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int s,m;
	cin>>s>>m;
	if(s>=9&&s<17){cout<<"don't call"<<endl;return 0;}
	if(s==17&&m==0){cout<<"don't call"<<endl;return 0;}
	cout<<"call";
	return 0;
}
