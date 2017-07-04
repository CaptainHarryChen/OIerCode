#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s[1005],stack[1005];
int main()
{
	gets(s);
	if(s[0]=='}'||s[0]==']'||s[0]==')'||s[0]=='>')
	{cout<<"no";return 0;}
	int len=strlen(s),a=0,f=1;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='{'||s[i]=='['||s[i]=='('||s[i]=='<')
			stack[a++]=s[i];
		else if(s[i]=='>')
		{
			if(stack[--a]=='<')stack[a]=0;
			else{f=0;break;}
		}
		else if(s[i]==')')
		{
			if(stack[--a]=='(')stack[a]=0;
			else{f=0;break;}
		}
		else if(s[i]==']')
		{
			if(stack[--a]=='[')stack[a]=0;
			else
				{f=0;break;}
		}
		else if(s[i]=='}')
		{
			if(stack[--a]=='{')stack[a]=0;
			else{f=0;break;}
		}
	}
	if(stack[0]!=0)f=0;
	if(f)cout<<"yes";
	else cout<<"no";
	return 0;
}
