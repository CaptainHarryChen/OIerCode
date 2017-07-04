#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
char s[10000];
int main()
{
	fgets(s,10000,stdin);
	int n=strlen(s),a=0,b=0,c=0,d=0;
	for(int i=0;i<n;i++)
	{
		if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z'))
			a++;
		else if(s[i]==' ')
			b++;
		else if(s[i]>='0'&&s[i]<='9')
			c++;
		else
			d++;
	}
	cout<<a<<endl<<b<<endl<<c<<endl<<d-1<<endl;
}
