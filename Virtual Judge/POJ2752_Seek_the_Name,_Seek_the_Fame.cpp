#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 400400
using namespace std;
char s[MAXN];
int nxt[MAXN],print[MAXN],p;
int main()
{
	while(~scanf("%s",s))
	{
		memset(nxt,0,sizeof nxt);
		memset(print,0,sizeof print);
		p=0;
		int len=strlen(s);
		nxt[0]=-1;
		for(int i=1;i<=len;i++)
		{
			int j=nxt[i-1];
			while(j!=-1&&s[j]!=s[i-1])
				j=nxt[j];
			nxt[i]=j+1;
		}
		print[p++]=len;
		int i=len;
		while(nxt[i])
		{print[p++]=nxt[i];i=nxt[i];}
		for(int i=p-1;i>=0;i--)
			printf("%d ",print[i]);
		printf("\n");
		memset(s,0,sizeof s);
	}
	return 0;
}
