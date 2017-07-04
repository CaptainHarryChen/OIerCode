#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 110005
char str[MAXN],temp[MAXN<<1];
int Len[MAXN<<1];
int Manachar(char *s)
{
	temp[0]='@';
	int len=strlen(s);
	for(int i=0;i<len;i++)
		temp[i*2+1]='#',temp[i*2+2]=s[i];
	temp[len*2+1]='#';
	temp[len*2+2]='$';
	temp[len*2+3]=0;
	int mx=0,po=0,ans=0;
	for(int i=1;i<=len*2+1;i++)
	{
		if(mx>i)
			Len[i]=min(mx-i,Len[2*po-i]);
		else
			Len[i]=1;
		while(temp[i+Len[i]]==temp[i-Len[i]])
			Len[i]++;
		if(i+Len[i]>mx)
		{
			mx=i+Len[i];
			po=i;
		}
		ans=max(ans,Len[i]);
	}
	return ans-1;
}
int main()
{
	while(~scanf("%s",str))
		printf("%d\n",Manachar(str));
	return 0;
}
