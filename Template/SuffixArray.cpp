#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005;

int n;
char str[MAXN];
int sa[MAXN],rk[MAXN],h[MAXN];
int cnt[MAXN],tsa[MAXN],trk[MAXN];

void GetSa()
{
	for(int i=1;i<=n;i++)
		cnt[(int)str[i]]++;
	for(int i=1;i<128;i++)
		cnt[i]+=cnt[i-1];
	for(int i=n;i>0;i--)
		sa[cnt[(int)str[i]]--]=i;
	for(int i=1;i<=n;i++)
		rk[sa[i]]=rk[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);
	for(int len=1;rk[sa[n]]<n;len<<=1)
	{
		for(int i=1;i<=n;i++)
			cnt[rk[sa[i]]]=i;
		for(int i=n;i>0;i--)
			if(sa[i]>len)
				tsa[cnt[rk[sa[i]-len]]--]=sa[i]-len;
		for(int i=n;i>n-len;i--)
			tsa[cnt[rk[i]]--]=i;
		for(int i=1;i<=n;i++)
			trk[tsa[i]]=trk[tsa[i-1]]+(rk[tsa[i]]!=rk[tsa[i-1]]||rk[tsa[i]+len]!=rk[tsa[i-1]+len]);
		swap(sa,tsa);
		swap(rk,trk);
	}
}
void GetH()
{
	int k=0;
	for(int i=1;i<=n;i++)
	{
		k=k>0?k-1:k;
		while(str[i+k]==str[sa[rk[i]+1]+k])
			k++;
		h[rk[i]]=k;
	}
}

int main()
{
	freopen("SuffixArray_data.in","r",stdin);
	scanf("%s",str+1);
	n=strlen(str+1);
	GetSa();
	GetH();
	for(int i=1;i<=n;i++)
	{
		printf("Sa[%2d]=%2d:  ",i,sa[i]);
		for(int j=sa[i];j<=n;j++)
			printf("%c",str[j]);
		printf("\n");
	}
	printf("\n");
	for(int i=1;i<n;i++)
		printf("Hight[%d~%d]=%d\n",i,i+1,h[i]);
	return 0;
}
