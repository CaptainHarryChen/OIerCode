#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	double n,m,s=0;
	cin>>n>>m;
	if(n>=m||n<=0||m>=1000000){cout<<"no answer"<<endl;return 0;}
	for(int i=n;i<=m;i++)
		s+=(1.0/i)*(1.0/i);
	printf("%.5lf\n",s);
	return 0;
}
