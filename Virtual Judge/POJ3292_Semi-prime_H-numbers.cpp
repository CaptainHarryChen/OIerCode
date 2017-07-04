#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1000005
bool noprime[MAXN];
int hprime[MAXN],pcnt;
int hsemip[MAXN];
int ans[MAXN];
int main()
{
	noprime[1]=1;
	for(int i=5;i<MAXN;i+=4)
		if(!noprime[i])
		{
			hprime[++pcnt]=i;
			if(i>1000)
				continue;
			for(int j=i*i;j<MAXN;j+=4*i)
				noprime[j]=1;
		}
	for(int i=1;hprime[i]<=MAXN/5;i++)
		for(int j=1,s=hprime[j]*hprime[i];j<=i&&s<MAXN;j++,s=hprime[j]*hprime[i])
			if(hsemip[s]==0)
				hsemip[s]=1;
	for(int i=1;i<MAXN;i++)
		ans[i]=ans[i-1]+(hsemip[i]==1);
	int n;
	while(scanf("%d",&n),n)
		printf("%d %d\n",n,ans[n]);
	return 0;
}
