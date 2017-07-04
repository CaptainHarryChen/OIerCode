#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    char s[15]={0};
	scanf("%s",s);
	int len=strlen(s),f=0;
	for(int i=0;i<len;i++)
		if(s[i]>='0')
		{f=1;break;}
	if(f&&len<=9)
		cout<<len<<endl;
	else
		cout<<"no answer"<<endl;
}
