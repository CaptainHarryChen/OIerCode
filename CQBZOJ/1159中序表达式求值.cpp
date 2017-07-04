#include<cstdio>
#include<iostream>
#include<stack>
#include<cstring>
#include<queue>
using namespace std;
char p[1000005];
struct fuhao
{
	char s;
	int lv;
	fuhao(){}
	fuhao(char c)
	{
		s=c;
		if(s=='+'||s=='-')
			lv=1;
		else if(s=='*'||s=='/')
			lv=2;
		else
			lv=0;
	}
	void shengji(int x){lv+=2*x;}
};
stack<fuhao>op;
stack<int>shu;
void jisuan()
{
	int b=shu.top();
	shu.pop();
	int a=shu.top(),ss=0;
	shu.pop();
	char s=op.top().s;
	op.pop();
	switch(s)
	{
		case '+':ss=a+b;break;
		case '-':ss=a-b;break;
		case '*':ss=a*b;break;
		case '/':ss=a/b;break;
	}
	shu.push(ss);
}
bool panduan()
{
	bool f;
	int t=shu.top();
	shu.pop();
	f=shu.empty();
	shu.push(t);
	return !f;
}
int main()
{
	int lvx=0,s=0;
	gets(p);
	int len=strlen(p);
	for(int i=0;i<=len;i++)
	{
		if(p[i]>='0'&&p[i]<='9')
		{
			int a=p[i]-'0';
			s*=10;
			s+=a;
		}
		else if(p[i]=='-'||p[i]=='+'||p[i]=='*'||p[i]=='/'||i==len)
		{
			shu.push(s);
			s=0;
			fuhao a(p[i]);
			a.shengji(lvx);
			if(!op.empty()&&a.lv<=op.top().lv)
			{
				do
				{
					jisuan();
				}while(!op.empty()&&a.lv<=op.top().lv);
			}
			op.push(a);
		}
		else if(p[i]=='(')
			lvx++;
		else if(p[i]==')')
			lvx--;
	}
	printf("%d\n",shu.top());
	return 0;
}
