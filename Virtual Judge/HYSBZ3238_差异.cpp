#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int n;
int sa[MAXN],rk[MAXN],sa1[MAXN],rk1[MAXN];
int cnt[MAXN];
int h[MAXN];
char str[MAXN];

void Calc()
{
	for(int i=1;i<=n;i++)
		cnt[str[i]-'a']++;
	for(int i=1;i<26;i++)
		cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--)
		sa[cnt[str[i]-'a']--]=i;
	rk[sa[1]]=1;
	for(int i=2;i<=n;i++)
		rk[sa[i]]=rk[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);
	for(int len=1;rk[sa[n]]<n;len<<=1)
	{
		for(int i=1;i<=n;i++)
			cnt[rk[sa[i]]]=i;
		for(int i=n;i>=1;i--)
			if(sa[i]-len>0)
				sa1[cnt[rk[sa[i]-len]]--]=sa[i]-len;
		for(int i=n;i>n-len;i--)
			sa1[cnt[rk[i]]--]=i;
		rk1[sa1[1]]=1;
		for(int i=2;i<=n;i++)
			rk1[sa1[i]]=rk1[sa1[i-1]]+(rk[sa1[i]]!=rk[sa1[i-1]]||rk[sa1[i]+len]!=rk[sa1[i-1]+len]);
		swap(sa,sa1);
		swap(rk,rk1);
	}
	for(int i=1,k=0;i<=n;i++)
	{
		k>0?k--:0;
		while(str[i+k]==str[sa[rk[i]+1]+k])
			k++;
		h[rk[i]]=k;
	}
}

long long ans=0;
int L[MAXN],R[MAXN];
int stk[MAXN],tp;

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	
	Calc();
	for(int i=1;i<=n;i++)
		ans+=1LL*i*(i-1)+1LL*i*(i-1)/2;
	
	stk[1]=1;tp=1;L[1]=1;
	for(int i=2;i<n;i++)
	{
		while(tp&&h[stk[tp]]>=h[i])
			tp--;
		L[i]=tp?stk[tp]+1:1;
		stk[++tp]=i;
	}
	stk[1]=n-1;tp=1;R[n-1]=n-1;
	for(int i=n-2;i>=1;i--)
	{
		while(tp&&h[stk[tp]]>h[i])
			tp--;
		R[i]=tp?stk[tp]-1:n-1;
		stk[++tp]=i;
	}
	
	for(int i=1;i<n;i++)
		ans-=2LL*h[i]*(i-L[i]+1)*(R[i]-i+1);
	printf("%lld\n",ans);
	
	return 0;
}
