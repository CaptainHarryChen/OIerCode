#include<cstdio>
#include<cstring>
const int MAXN=100005;

char str[MAXN];

int main()
{
	scanf("%s",str);
	int n=strlen(str);
	int cnt=0;
	for(int i=0;i<n;i++)
		cnt+=(str[i]=='1');
	bool flag=false;
	for(int i=0;i<n;i++)
	{
		if(str[i]=='0')
			putchar('0');
		if(str[i]=='1')
			continue;
		if(str[i]=='2')
		{
			if(!flag)
			{
				for(int j=1;j<=cnt;j++)
					putchar('1');
				flag=true;
			}
			putchar('2');
		}
	}
	if(!flag)
		for(int j=1;j<=cnt;j++)
			putchar('1');
	
	return 0;
}
