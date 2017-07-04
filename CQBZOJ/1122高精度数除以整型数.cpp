#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char a[505],s[505];
int b;
void chuli(char *a)
{
	int len=strlen(a);
	for(int i=0;i<len;i++)
		a[i]-='0';
}
int main()
{
	scanf("%s%d",a,&b);
	int len=strlen(a);
	chuli(a);
	int k;
	int ss=0;
	for(int i=0;i<len;i++)
    {
        ss=ss*10+a[i];
		s[i]=ss/b;
        ss%=b;
		k=i;
    }
	int ii;
	for(ii=0;s[ii]==0&&ii<=k;ii++);
	if(ii==k+1)
		printf("0\n");
	else{
	for(;ii<=k;ii++)
		printf("%c",s[ii]+'0');
	printf("\n");}
	printf("%d\n",ss);
	return 0;
}
