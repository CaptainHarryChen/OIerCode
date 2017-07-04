#include<cstdio>
#include<iostream>
using namespace std;
int n,cnt;
bool b[15],c[30],d[30];
void f(int z)
{
	if(z==n)
	{
		cnt++;
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(b[i]||c[z-i+n]||d[z+i])continue;
		b[i]=c[z-i+n]=d[z+i]=1;
		f(z+1);
		b[i]=c[z-i+n]=d[z+i]=0;
	}
}
int main()
{
	scanf("%d",&n);
	f(0);
	printf("%d\n",cnt);
	return 0;
}
