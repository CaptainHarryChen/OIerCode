#include<iostream>
#include<cstdio>
using namespace std;
char s[10];
bool f()
{
	for(int i=0;i<10;i++)
		if(s[i]=='0')
			return 0;
	for(char e='1';e<='9';e++)
		for(int i=0,cnt=0;i<10;i++)
		{
			if(s[i]==e)
				cnt++;
			if(cnt>=2)
				return 0;
		}
	return 1;
}
int main()
{
	int a,b,c,n;
	cin>>n;
	for(int i=100,cnt=0;i*3<1000;i++)
	{
		a=i;b=i*2;c=i*3;
		sprintf(s,"%d%d%d",a,b,c);
		if(f())
			cnt++;
		if(cnt==n)
		{printf("%d %d %d\n",a,b,c);return 0;}
	}
	return 0;
}
