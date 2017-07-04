#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 200
int P,dis[MAXN],E[MAXN][MAXN];
bool used[MAXN];
int main()
{
	scanf("%d",&P);
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<MAXN;j++)
			E[i][j]=0x3FFFFFFF;
	for(int i=1;i<=P;i++)
	{
		char x[2],y[2];
		int v;
		scanf("%s %s %d",x,y,&v);
		E[(int)x[0]][(int)y[0]]=min(E[(int)x[0]][(int)y[0]],v);
		E[(int)y[0]][(int)x[0]]=min(E[(int)y[0]][(int)x[0]],v);
	}
	for(int i=1;i<MAXN;i++)
		dis[i]=0x3FFFFFFF;
	dis['Z']=0;
	for(int i=1;i<=MAXN;i++)
	{
		int mind=0x7FFFFFFF,k;
		for(int j=1;j<MAXN;j++)
			if(!used[j]&&mind>dis[j])
			{mind=dis[j];k=j;}
		used[k]=1;
		for(int j=1;j<MAXN;j++)
			if(dis[j]>dis[k]+E[k][j])
				dis[j]=dis[k]+E[k][j];
	}
	int minc=0x7FFFFFFF,kk;
	for(int i='A';i<'Z';i++)
		if(minc>dis[i])
			{minc=dis[i];kk=i;}
	printf("%c %d\n",kk,dis[kk]);
	return 0;
}
