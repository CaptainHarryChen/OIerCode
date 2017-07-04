#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXA 1000100
#define MAXB 1000100
using namespace std;
char A[MAXA],B[MAXB];
int nxt[MAXB];
int main()
{
	scanf("%s%s",A,B);
	int len1=strlen(A),len2=strlen(B),d=-1;
	nxt[0]=-1;
	for(int i=1;i<len2;i++)
	{
		int j=nxt[i-1];
		while(j!=-1&&B[j]!=B[i-1])
			j=nxt[j];
		nxt[i]=j+1;
	}
	for(int i=0,j=0;i<=len1;i++,j++)
	{
		while(j!=-1&&B[j]!=A[i-1])
			j=nxt[j];
		if(j==len2-1){d=i-j;break;}
	}
	if(d!=-1)
		printf("yes\n%d\n",d-1);
	else
		printf("no\n");
	return 0;
}
