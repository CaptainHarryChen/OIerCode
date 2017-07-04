#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 50050
#define INF 9223372036854775807
using namespace std;
long long N,D,H[MAXN],choc[MAXN];
void Find_X(long long L,long long R)
{
	if(L>R)return;
	long long mid=(L+R+1)>>1,happy=0,cnt=1;
	bool f=1;
	memset(choc,0,sizeof choc);
	for(int i=1;i<=D;i++)
	{
		happy>>=1;
		while(happy<mid&&cnt<=N)
		{
			happy+=H[cnt];
			choc[cnt++]=i;
		}
		if(happy<mid){f=0;break;}
	}
	if(L==R)
	{
		if(!f)return;
		printf("%lld\n",mid);
		for(int i=1;i<=N;i++)
		{
			if(choc[i]==0)
				printf("%lld\n",D);
			else
				printf("%lld\n",choc[i]);
		}
		exit(0);
	}
	if(f)
		Find_X(mid,R);
	else
		Find_X(L,mid-1);
}
int main()
{
	scanf("%lld%lld",&N,&D);
	long long s=0;
	for(long long i=1;i<=N;i++)
	{scanf("%lld",&H[i]);s+=H[i];}
	Find_X(0,s);
	return 0;
}
