#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,cnt;
bool num[10];
bool cheak(int x,int len)
{
	char s[10];
	sprintf(s,"%d",x);
	int m=strlen(s);
	if(m!=len)return 0;
	for(int i=0;i<m;i++)
		if(!num[s[i]-'0'])
			return 0;
	return 1;
}
int main()
{
	int x;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		num[x]=1;
	}
	for(int i=100;i<1000;i++)
	{
		if(!cheak(i,3))continue;
		for(int j=10;j<100;j++)
		{
			if(!cheak(j,2))continue;
			int a=(j%10)*i;
			if(!cheak(a,3))continue;
			int b=(j/10)*i;
			if(!cheak(b,3))continue;
			int c=a+b*10;
			if(!cheak(c,4))continue;
			cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
