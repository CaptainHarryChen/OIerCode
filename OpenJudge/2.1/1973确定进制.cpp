#include<cstdio>
#include<cstring>
using namespace std;
int f(char s[],int b)
{
	int len=strlen(s),x=0;
	for(int i=0;i<len;i++)
	{
		x*=b;
		if(s[i]>='0'&&s[i]<='9')
		{
			if(s[i]-'0'>=b)
				return -1;
			x+=(s[i]-'0');
		}
		else if(s[i]>='A')
		{
			if(s[i]-'A'+10>=b)
				return -1;
			x+=(s[i]-'A'+10);
		}
	}
	return x;
}
int main()
{
	int n;
	bool flag=0;
	scanf("%d",&n);
	while(n--)
	{
		flag=0;
		char a[35],b[35],c[35];
		scanf("%s%s%s",a,b,c);
		for(int i=2;i<=16;i++)
		{
			int x=f(a,i),y=f(b,i),z=f(c,i);
			if(x==-1||y==-1||z==-1)continue;
			if(x*y==z)
			{printf("%d\n",i);flag=1;break;}
		}
		if(!flag)printf("0\n");
	}
	return 0;
}
