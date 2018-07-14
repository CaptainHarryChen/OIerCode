#include<cstdio>
#include<cstring>
const int MAXN=100005;

int n;
char str[MAXN];
int cnt[30];

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	if(n==2)
	{
		if(str[1]==str[2])
			puts("1 2");
		else
			puts("-1 -1");
		return 0;
	}
	for(int i=1;i+2<=n;i++)
	{
		if(str[i]==str[i+1]||str[i]==str[i+2]||str[i+1]==str[i+2])
		{
			printf("%d %d\n",i,i+2);
			return 0;
		}
	}
	puts("-1 -1");
	
	return 0;
}
