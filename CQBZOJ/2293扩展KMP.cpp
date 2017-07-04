#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXA 1000100
#define MAXB 20020
using namespace std;
char A[MAXA],B[MAXB];
int nxt[MAXB],ex[MAXA],len1,len2;
void get_nxt()
{
	nxt[0]=len2;
	for(int i=1;B[i]==B[i-1];i++)
		nxt[1]=i;
	int maxp=nxt[1]+1,j=1,k=0;
	for(int i=2;i<len2;i++)
	{
		if(i+nxt[i-j]<maxp)
			nxt[i]=nxt[i-j];
		else
		{
			for(k=max(i,maxp);k<len2&&B[k]==B[k-i];k++);
			j=i;
			nxt[i]=k-i;
			maxp=i+nxt[i];
		}
	}
}
void get_ex()
{
	int i,j,k;
	for(i=0,j=0;i<len1&&j<len2&&A[i]==B[j];i++,j++);
	ex[0]=j;
	for(i=1,j=0;i<len1&&j<len2&&A[i]==B[j];i++,j++);
	ex[1]=j;
	int maxp=j+1,maxi=1;
	for(int i=2;i<len1;i++)
	{
		if(i+nxt[i-maxi]<maxp)
			ex[i]=nxt[i-maxi];
		else
		{
			for(k=max(i,maxp);A[k]==B[k-i]&&k<len1&&k-i<len2;k++);
			maxp=k;
			maxi=i;
			ex[i]=k-i;
		}
	}
}
int main()
{
	scanf("%s%s",A,B);
	len1=strlen(A),len2=strlen(B);
	get_nxt();
	/*for(int i=0;i<len2;i++)
		printf("%d ",nxt[i]);
	printf("\n");*/
	get_ex();
	for(int i=0;i<len1-1;i++)
		printf("%d ",ex[i]);
	printf("%d",ex[len1-1]);
	return 0;
}
