#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int len;
char s[10000];
struct wor
{
	char w[50];
}word[205];
bool bijiao(wor a,wor b)
{
	if(strcmp(a.w,b.w)<0)
		return 1;
	return 0;
}
int main()
{
	while(gets(s))
	{
		int i;
		char *p=s;
		if(s[0]==0)
		{printf("0\n");continue;}
		while(*p==' ')p++;
		for(i=0;;i++)
		{
			sscanf(p,"%s",word[i].w);
			p+=strlen(word[i].w);
			while(*p==' ')p++;
			if(*p==0){i++;break;}
		}
		printf("%d ",i);
		sort(word,word+i,bijiao);
		for(int j=0;j<i-1;j++)
			printf("%s ",word[j].w);
		printf("%s\n",word[i-1].w);
		memset(s,0,sizeof s);
		memset(word,0,sizeof word);
	}
	return 0;
}
