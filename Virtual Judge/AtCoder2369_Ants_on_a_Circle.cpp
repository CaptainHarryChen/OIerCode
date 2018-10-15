#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N,L,T,X[MAXN];

int main()
{
	scanf("%d%d%d",&N,&L,&T);
	int pos=0;
	for(int i=1;i<=N;i++)
	{
		int flag;
		scanf("%d%d",&X[i],&flag);
		if(flag==2)
			flag=-1;
		pos+=(X[i]+flag*T)/L;
		X[i]=(X[i]+flag*T)%L;
		if(X[i]<0)
			X[i]+=L,pos--;
	}
	pos=(pos%N+N)%N;
	sort(X+1,X+N+1);
	for(int i=pos+1;i<=N;i++)
		printf("%d\n",X[i]);
	for(int i=1;i<=pos;i++)
		printf("%d\n",X[i]);
	
	return 0;
}
