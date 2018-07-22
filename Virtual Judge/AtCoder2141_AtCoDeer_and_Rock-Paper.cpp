#include<cstdio>
#include<cstring>
const int MAXN=100005;

char str[MAXN];

int main()
{
	scanf("%s",str);
	int n=strlen(str),cnt=0;
	for(int i=0;i<n;i++)
		cnt+=str[i]=='p';
	int ans=(n/2)-cnt;
	printf("%d\n",ans);
	
	return 0;
}
