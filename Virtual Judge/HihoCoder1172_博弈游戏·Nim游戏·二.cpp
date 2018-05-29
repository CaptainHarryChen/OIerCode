#include<cstdio>
const int MAXN=10005;

char str[MAXN];

int main()
{
	int n,ans=0;
	scanf("%d%s",&n,str);
	for(int i=0;i<n;i++)
		if(str[i]=='H')
			ans^=i+1;
	if(ans)
		puts("Alice");
	else
		puts("Bob");
	return 0;
}
