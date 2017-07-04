#include<cstdio>
#include<iostream>
#include<cstring>
#define INF 2139062143
#define MAXN 3030
using namespace std;
int R,S,at=INF,al=INF,ar,au,maxfall=INF;
char pic[MAXN][MAXN];
void fall(int x)
{
	if(x==0)
		return;
	for(int i=au,j=au+x;i>=at;i--,j--)
		for(int k=al;k<=ar;k++)
			if(pic[i][k]=='X')
				swap(pic[i][k],pic[j][k]);
}
int main()
{
	scanf("%d%d",&R,&S);
	for(int i=1;i<=R;i++)
		for(int j=1;j<=S;j++)
		{
			scanf("%c",&pic[i][j]);
			if(pic[i][j]!='.'&&pic[i][j]!='#'&&pic[i][j]!='X'){j--;continue;}
			if(pic[i][j]=='X')
			{
				if(i<at)at=i;
				if(j<al)al=j;
				if(i>au)au=i;
				if(j>ar)ar=j;
			}
		}
	for(int i=al;i<=ar;i++)
	{
		int j=0,k=0;
		while(pic[j][i]!='#')j++;
		j--;
		while(pic[j][i]!='X'&&j!=0){j--;k++;}
		if(j==0)k=INF;
		if(maxfall>k)
			maxfall=k;
	}
	fall(maxfall);
	for(int i=1;i<=R;i++)
		printf("%s\n",pic[i]+1);
	return 0;
}
