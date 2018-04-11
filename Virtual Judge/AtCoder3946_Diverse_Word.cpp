#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main()
{
	char s[30],t[30];
	scanf("%s",s);
	int n=strlen(s);
	if(n==26)
	{
		copy(s,s+n,t);
		if(!next_permutation(s,s+n))
			puts("-1");
		else
		{
			for(int i=0;i<n;i++)
				if(s[i]!=t[i])
				{
					s[i+1]=0;
					break;
				}
			puts(s);
		}
	}
	else
	{
		printf(s);
		bool vis[30]={false};
		for(int i=0;i<n;i++)
			vis[s[i]-'a']=true;
		for(int i=0;i<26;i++)
			if(!vis[i])
			{
				printf("%c\n",i+'a');
				break;
			}
	}
	return 0;
}
