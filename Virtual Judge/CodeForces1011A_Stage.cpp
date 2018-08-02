#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=53;

int n,k;
int cnt[MAXN];
char s[MAXN];

int main()
{
	scanf("%d%d%s",&n,&k,s+1);
	for(int i=1;i<=n;i++)
		cnt[s[i]-'a']++;
	int ans=0,last=-100;
	for(int i=1,j;i<=k;i++)
	{
		for(j=max(last+1,0);j<26;j++)
			if(cnt[j]&&(last-j>1||j-last>1))
				break;
		if(j>=26)
		{puts("-1");return 0;}
		ans+=j+1;
		cnt[j]--;
		last=j;
	}
	printf("%d\n",ans);
	
	return 0;
}
