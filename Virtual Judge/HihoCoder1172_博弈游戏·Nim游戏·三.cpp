#include<cstdio>
const int MAXN=105,MAXA=20005;

int sg[MAXN];
int N,A;

int main()
{
	int ans=0;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&A);
		if(A&&A%4==0)
			ans^=A-1;
		else if(A%4==3)
			ans^=A+1;
		else
			ans^=A;
	}
	
	if(ans)
		puts("Alice");
	else
		puts("Bob");
	
	return 0;
}
