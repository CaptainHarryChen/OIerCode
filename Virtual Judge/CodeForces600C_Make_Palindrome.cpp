#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005;

char s[MAXN];
int cnt[30];
vector<int> odd;
char ans[MAXN];

int main()
{
	scanf("%s",s);
	int n=strlen(s);
	for(int i=0;i<n;i++)
		cnt[s[i]-'a']++;
	for(int i=0;i<26;i++)
		if(cnt[i]%2==1)
			odd.push_back(i);
	
	int t;
	for(int i=odd.size()-1,j=0;i>j;i--,j++,t=i)
	{
		cnt[odd[i]]--;
		cnt[odd[j]]++;
	}
	int pos=0;
	for(int i=0;i<26;i++)
		for(int j=1;j<=cnt[i]/2;j++)
			ans[pos++]=i+'a';
	if(n%2==1)
		ans[pos++]=odd[t]+'a';
	for(int i=n/2-1;i>=0;i--)
		ans[pos++]=ans[i];
	puts(ans);
	
	return 0;
}
