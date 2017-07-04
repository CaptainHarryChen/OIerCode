#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
char x[1005];
using namespace std;
int main()
{
	int a,s,d,f;
	a=s=d=f=0;
    gets(x);
	for(int i=0;x[i]!='#';i++)
	{
		if(x[i]=='a')
			a++;
		else if(x[i]=='s')
			s++;
		else if(x[i]=='d')
			d++;
		else if(x[i]=='f')
			f++;
	}
	printf("a:%d\ns:%d\nd:%d\nf:%d\n",a,s,d,f);
	return 0;
}
