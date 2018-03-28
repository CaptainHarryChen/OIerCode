#include<cstdio>
const int MAXN=100;

char grid[MAXN+5][MAXN+5];

int main()
{
	int A,B,i,j;
	scanf("%d%d",&A,&B);
	for(i=0;i<MAXN/2;i++)
		for(j=0;j<MAXN;j++)
			grid[i][j]='.';
	for(int i=MAXN/2;i<MAXN;i++)
		for(j=0;j<MAXN;j++)
			grid[i][j]='#';
	A--;B--;
	for(i=MAXN-1;A;i-=2)
		for(j=0;j<MAXN&&A;j+=2)
			grid[i][j]='.',A--;
	for(i=0;B;i+=2)
		for(j=0;j<MAXN&&B;j+=2)
			grid[i][j]='#',B--;
	printf("%d %d\n",MAXN,MAXN);
	for(i=0;i<MAXN;i++)
		puts(grid[i]);
	return 0;
}
