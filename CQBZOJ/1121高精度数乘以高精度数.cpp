#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char a[505],b[505],s[1200];
void chuli(char *a)
{
	int len=strlen(a);
	for(int i=0;i<len;i++)
		a[i]-='0';
}
int main()
{
	scanf("%s%s",a,b);
	int len1=strlen(a),len2=strlen(b);
	chuli(a);
	chuli(b);
	for(int i=0;i<len1;i++)
	{
		for(int j=0;j<len2;j++)
		{
			s[i+j+1]+=a[i]*b[j];
			for(int k=i+j+1;s[k]>9;k--)
			{
				s[k-1]+=s[k]/10;
				s[k]%=10;
			}
		}
	}
	int ii=0;
	for(ii=0;s[ii]==0&&ii<len1+len2;ii++);
	if(ii==len1+len2)
	{printf("0");return 0;}
	for(;ii<len1+len2;ii++)
		printf("%c",s[ii]+'0');
	printf("\n");
	return 0;
}
