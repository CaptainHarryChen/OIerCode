#include<cstdio>
#include<cstring>
#define MAXN 260
int n,m,num[MAXN][MAXN];
void fenzhi(int x,int y,int len,int s)
{
	if(len==1)
	{
		num[x][y]=s;
		return;
	}
	fenzhi(x,y,len/2,s);
	fenzhi(x+len/2,y,len/2,s+len/2);
	for(int i=0;i<len/2;i++)
		memcpy(num[x+len/2+i]+y+len/2,num[x+i]+y,len*2);
	for(int i=0;i<len/2;i++)
		memcpy(num[x+i]+y+len/2,num[x+len/2+i]+y,len*2);
}
int main()
{
	scanf("%d",&m);
	n=1<<m;
	fenzhi(1,1,n,1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<n;j++)
			printf("%d ",num[i][j]);
		printf("%d\n",num[i][n]);
	}
	return 0;
}
