#include<cstdio>
#include<iostream>
#include<cstring>
#define INF 2139062143
#define MAXS 1000100
#define MAXN 100001000
using namespace std;
int letter[30],k;
long long n;
char word[MAXS];
int ksc(long long x,long long y,int r)
{
	long long m=0;
	for(long long i=1;i<=y;i<<=1,x=(x<<1)%r)
		if(y&i)
			m=(x+m)%r;
	return m;
}
int main()
{
	scanf("%lld%s",&n,word);
	int len=strlen(word);
	for(int i=0;i<len;i++)
		letter[word[i]-'A']++;
	scanf("%d",&k);
	long long a;
	char c;
	for(int i=1;i<=k;i++)
	{
		scanf("%lld %c",&a,&c);
		long long cnt=(long long)(a/len)*letter[c-'A'];
		if(a%len==0){printf("%I64d\n",cnt);continue;}
		long long x=a,y=a-1;
		if(x%2==0)x/=2;
		else y/=2;
		int l=(ksc(x,y,len)+1)%len;
		if(l==0)l=len;
		x=a,y=a+1;
		if(x%2==0)x/=2;
		else y/=2;
		int r=ksc(x,y,len)%len;
		if(r==0)r=len;
		for(int j=l;j!=r;j++,j%=len)
			if(word[j==0?len:j-1]==c)
				cnt++;
		if(word[r-1]==c)cnt++;
		printf("%lld\n",cnt);
	}
	return 0;
}
