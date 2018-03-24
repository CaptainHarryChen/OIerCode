#include<cstdio>
#include<cstdlib>

int N,rest=20;

int Query(int pos)
{
	char str[20];
	rest--;
	printf("%d\n",pos);
	fflush(stdout);
	scanf("%s",str);
	if(str[0]=='V')
		exit(0);
	if(str[0]=='M')
		return 1;
	if(str[0]=='F')
		return 2;
	return -1;
}

void solve(int L,int R,int st1=-1)
{
	if(R-L+(st1==-1)<=rest)
	{
		for(int i=L+(st1!=-1);i<=R;i++)
			if(Query(i)==0)
				exit(0);
		exit(0);
	}
	if(st1==-1)
		st1=Query(L);
	int mid=(R-L+1)/2;
	if(mid%2==1)
		mid++;
	int st2=Query(L+mid);
	if(st1==st2)
		solve(L+mid,R,st2);
	else
		solve(L,L+mid,st1);
}

int main()
{
	scanf("%d",&N);
	solve(0,N-1);
	
	return 0;
}
