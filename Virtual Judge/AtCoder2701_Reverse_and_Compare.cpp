#include<cstdio>
#include<cstring>
const int MAXN=200005;

int n;
char str[MAXN];
int cnt[30];

int main()
{
	scanf("%s",str);
	n=strlen(str);
	for(int i=0;i<n;i++)
		cnt[str[i]-'a']++;
	long long ans=1LL*n*(n-1)/2;
	for(int i=0;i<26;i++)
		ans-=1LL*cnt[i]*(cnt[i]-1)/2;
	ans++;
	printf("%lld\n",ans);
	
	return 0;
}
