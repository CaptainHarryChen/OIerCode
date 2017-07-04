#include<cstdio>
#include<iostream>
using namespace std;
int n,x,y,s[100][100],cnt=1,dd[4][2]={{0,0},{0,1},{1,0},{1,1}};
void f(int a,int b,int len,int c,int d)
{
	if(len==2)
	{
		for(int i=a;i<a+len;i++)
			for(int j=b;j<b+len;j++)
			{
				if(i==c&&j==d)continue;
				s[i][j]=cnt;
			}
		cnt++;
			/*for(int i=0;i<n;i++)
	{
		printf("%d",s[i][0]);
		for(int j=1;j<n;j++)
			printf(" %d",s[i][j]);
		printf("\n");
	}
	printf("\n");*/
		return;
	}
	int id;
	if(c<=a+len/2-1&&d<=b+len/2-1)id=0;
	else if(c>a+len/2-1&&d<=b+len/2-1)id=2;
	else if(c<=a+len/2-1&&d>b+len/2-1)id=1;
	else if(c>a+len/2-1&&d>b+len/2-1)id=3;
	for(int i=0;i<4;i++)
	{
		if(i==id)continue;
		s[a+len/2+dd[i][0]-1][b+len/2+dd[i][1]-1]=cnt;
	}
	cnt++;
	/*for(int i=0;i<n;i++)
	{
		printf("%d",s[i][0]);
		for(int j=1;j<n;j++)
			printf(" %d",s[i][j]);
		printf("\n");
	}
	printf("\n");*/
	if(id!=0)f(a,b,len/2,a+len/2-1,b+len/2-1);
	else f(a,b,len/2,c,d);
	if(id!=2)f(a+len/2,b,len/2,a+len/2,b+len/2-1);
	else f(a+len/2,b,len/2,c,d);
	if(id!=1)f(a,b+len/2,len/2,a+len/2-1,b+len/2);
	else f(a,b+len/2,len/2,c,d);
	if(id!=3)f(a+len/2,b+len/2,len/2,a+len/2,b+len/2);
	else f(a+len/2,b+len/2,len/2,c,d);
}
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	x--;y--;
	f(0,0,n,x,y);
	for(int i=0;i<n;i++)
	{
		printf("%d",s[i][0]);
		for(int j=1;j<n;j++)
			printf(" %d",s[i][j]);
		printf("\n");
	}
	return 0;
}
