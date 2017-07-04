#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int N;
int count(int a,int b,int c,int d)
{
	if(b+d>N)
		return 1;
	if(b+d==N)
		return 2;
	int cnt=0;
	cnt+=count(a,b,a+c,b+d);
	cnt+=count(a+c,b+d,c,d);
	return cnt;
}
int main()
{
	scanf("%d",&N);
	printf("%d\n",count(0,1,1,1)+1);
	return 0;
}
