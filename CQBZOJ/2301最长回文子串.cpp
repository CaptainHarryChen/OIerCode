#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 2005
char S[MAXN];
char temp[MAXN<<1];
int P[MAXN<<1];
void Manacher(int n)
{
	temp[0]='*';
	temp[1]='#';
	for(int i=0;i<n;i++)
	{
		temp[i*2+2]=S[i];
		temp[i*2+3]='#';
	}
	temp[n*2+2]='&';
	int mx=0,po;
	for(int i=1;i<=2*n+1;i++)
	{
		if(i<=mx)
			P[i]=min(mx-i+1,P[po*2-i]);
		else
			P[i]=0;
		while(temp[i+P[i]]==temp[i-P[i]])
			P[i]++;
		if(mx<i+P[i]-1)
		{
			mx=i+P[i]-1;
			po=i;
		}
	}
}
int main()
{
	scanf("%s",S);
	int n=strlen(S);
	Manacher(n);
	int mx=0,k;
	for(int i=1;i<=n*2+1;i++)
		if(mx<P[i])
		{mx=P[i];k=i;}
	for(int i=k-P[k]+1;i<=k+P[k]-1;i++)
		if(temp[i]!='#')
			printf("%c",temp[i]);
	printf("\n");
	return 0;
}
