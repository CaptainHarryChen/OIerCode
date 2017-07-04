#include<cstdio>
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int main()
{
	int v,d,time=0,cnt=1,s=0;
	cin>>v>>d;
	while(s<=v)
	{
		for(int i=0;i<cnt;i++)
		{
			time++;s+=d;
			if(s>=v)
			{
				printf("%d\n",time);
				return 0;
			}
		}
		time++;cnt++;
	}
	printf("%d\n",time);
	return 0;
}
 