#include<cstdio>
#include<cstring>
const int MAXN=105;

char s[MAXN];

int main()
{
	int n;
	while(scanf("%s",s)!=EOF)
	{
		n=strlen(s);
		int cnt1=0,cnt0=0;
		for(int i=0;i<n-1;i++)
			if(s[i]=='0'&&s[i+1]=='0')
				cnt1++;
		cnt1+=s[n-1]=='0'&&s[0]=='0';
		for(int i=0;i<n;i++)
			cnt0+=s[i]=='0';
		if(cnt1*n<cnt0*cnt0)
			puts("ROTATE");
		else if(cnt1*n>cnt0*cnt0)
			puts("SHOOT");
		else
			puts("EQUAL");
	}
	return 0;
}
