#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int N,cnts[7];
bool Leap(int x)
{
	if(x%4!=0||x==0||x==200||x==300)
		return 0;
	return 1;
}
int main()
{
	scanf("%d",&N);
	N--;
	for(int i=0,x=13%7;i<=N;i++)
	{
		bool leap_year=Leap(i);
		month[2]=28+leap_year;
		for(int j=1;j<=12;j++)
		{
			cnts[x]++;
			x+=month[j];
			x=x%7;
		}
	}
	printf("%d %d ",cnts[6],cnts[0]);
	for(int i=1;i<=4;i++)
		printf("%d ",cnts[i]);
	printf("%d\n",cnts[5]);
	return 0;
}
