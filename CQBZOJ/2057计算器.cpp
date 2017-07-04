#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
char s[1000];
int a[3];
int main()
{
	gets(s);
	int len=strlen(s),k,n,x=0,key=0;
	for(int i=len-1,j,m=0;i>=0;i--)
	{
		if((s[i]>='0'&&s[i]<='9'))
		{
			for(j=i,k=1,m=0;s[j]>='0'&&s[j]<='9';j--,k++)
			{
				n=1;
				for(int l=1;l<k;l++)
					n*=10;
				m+=(s[j]-'0')*n;
				i=j;
			}
			a[x++]=m;
		}
		else
			switch(s[i])
			{
				case '+':key=1;break;
				case '-':key=2;break;
				case '*':key=3;break;
				case '/':key=4;break;
			}
	}
	switch(key)
	{
		case 1:cout<<a[0]+a[1]<<endl;break;
		case 2:cout<<a[1]-a[0]<<endl;break;
		case 3:cout<<a[0]*a[1]<<endl;break;
		case 4:cout<<a[1]/a[0]<<endl;break;
	}
	return 0;
}
