#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n[3][3],max=0,min=999999,p1,q1,p2,q2;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			cin>>n[i][j];
			if(n[i][j]>max)
			{max=n[i][j];p1=i+1;q1=j+1;}
			if(n[i][j]<min)
			{min=n[i][j];p2=i+1;q2=j+1;}
		}
	printf("max=%d (%d,%d)\nmin=%d (%d,%d)\n",max,p1,q1,min,p2,q2);
	return 0;
}
