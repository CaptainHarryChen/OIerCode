#include<cstdio>
#include<cstring>
const int MAXN=100;

char s[MAXN];

int main()
{
	scanf("%s",s);
	int n=strlen(s);
	int ans=0;
	for(int i=0;i<n;i++)
		ans+=s[i]=='1'||s[i]=='3'||s[i]=='5'||s[i]=='7'||s[i]=='9'
		||s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u';
	printf("%d\n",ans);
	return 0;
}
