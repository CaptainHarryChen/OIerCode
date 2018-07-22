#include<cstdio>
#include<cstring>
using namespace std;
const int HASH=10007U,HASHMOD=998244353;
const int MAXN=500005;

char W[MAXN];
int hash[MAXN],powhash[MAXN];
int GetHash(int L,int R)
{
	return ((hash[R]-1LL*hash[L-1]*powhash[R-L+1]%HASHMOD)%HASHMOD+HASHMOD)%HASHMOD;
}

bool pref[MAXN],suff[MAXN];

int main()
{
	scanf("%s",W+1);
	int n=strlen(W+1);
	hash[0]=0;powhash[0]=1;
	for(int i=1;i<=n;i++)
	{
		hash[i]=(1LL*hash[i-1]*HASH%HASHMOD+W[i]-'a')%HASHMOD;
		powhash[i]=(1LL*powhash[i-1]*HASH)%HASHMOD;
	}
	
	for(int d=1;d<=n;d++)
		for(int i=d+d;i<=n;i+=d)
			if(GetHash(1,i-d)==GetHash(d+1,i))
				pref[i]=true;
	for(int d=1;d<=n;d++)
		for(int i=n-d-d+1;i>=1;i-=d)
			if(GetHash(i,n-d)==GetHash(i+d,n))
				suff[i]=true;
	if(!pref[n])
	{
		printf("%d\n%d\n",1,1);
		return 0;
	}
	int cnt=0;
	for(int i=1;i<n;i++)
		if(!pref[i]&&!suff[i+1])
			cnt++;
	if(cnt)
	{
		printf("2\n%d\n",cnt);
		return 0;
	}
	printf("%d\n%d\n",n,1);
	
	return 0;
}
