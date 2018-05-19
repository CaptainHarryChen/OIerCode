#include<cstdio>
#include<algorithm>
using namespace std;

int getnum(const char c[])
{
	if(c[0]=='A')return 14;
	if(c[0]=='J')return 11;
	if(c[0]=='Q')return 12;
	if(c[0]=='K')return 13;
	if(c[0]=='1'&&c[1]=='0')return 10;
	return c[0]-'0';
}
char getcol(char c[])
{
	if(c[1]=='0')
		return c[2];
	return c[1];
}

struct card
{
	char s[5];
	bool operator < (const card &t)const
	{
		int a=getnum(s),b=getnum(t.s);
		return a<b;
	}
};

int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}
card c[4];

int getans()
{
	sort(c,c+4);
	bool flag1=false,flag2=true;
	for(int i=0;i<3;i++)
	{
		if((getnum(c[i+1].s)-getnum(c[i].s)>2)||(getnum(c[i+1].s)-getnum(c[i].s)==0))
			return 0;
		else if(getnum(c[i+1].s)-getnum(c[i].s)==2)
		{
			if(flag1)
				return 0;
			flag1=true;
		}
		if(getcol(c[i].s)!=getcol(c[3].s))
			flag2=false;
	}
	if(flag1==false&&(c[3].s[0]=='A'||c[0].s[0]=='2'))
		flag1=true;
	return (2-flag1)*(4-flag2);
}

int main()
{
	while(scanf("%s%s%s%s",c[0].s,c[1].s,c[2].s,c[3].s)!=EOF)
	{
		int x=getans(),y=48;
		int d=gcd(x,y);
		x/=d;y/=d;
		printf("%d/%d\n",x,y);
	}
	
	return 0;
}
