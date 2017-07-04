#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int main()
{
	int y;
	cin>>y;
	if((y%4==0&&y%100!=0)||(y%400==0))
		cout<<"TRUE"<<endl;
	else
		cout<<"FALSE"<<endl;
	return 0;
}
