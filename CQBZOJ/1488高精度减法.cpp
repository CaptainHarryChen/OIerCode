#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char a[300],b[300];
void chuli(char *a)
{
    int len=strlen(a);
    for(int i=len-1,j=299;i>=0;i--,j--){a[j]=a[i];a[i]=0;}
    for(int i=0;i<300;i++)
        if(a[i]!=0)
            a[i]-='0';
}
int bijiao(char *a,char *b)
{
	int len1=strlen(a),len2=strlen(b);
	if(len1>len2)return 1;
	if(len1<len2)return -1;
	if(len1==len2)return strncmp(a,b,len1);
}
int main()
{
    scanf("%s%s",a,b);
    int len1=strlen(a),len2=strlen(b);
    int len=len1>len2?len1:len2,f=bijiao(a,b);
    chuli(a);
    chuli(b);
	if(f>0)
		for(int i=299;i>=300-len;i--)
		{
			if(a[i]<b[i]){a[i]+=10;a[i-1]--;}
			a[i]-=b[i];
		}
	else if(f==0)
	{printf("0\n");return 0;}
	else
	{
		printf("-");
		for(int i=299;i>=300-len;i--)
		{
			if(a[i]>b[i]){b[i]+=10;b[i-1]--;}
			a[i]=b[i]-a[i];
		}
	}
    int i=0;
    while(!a[i])i++;
    for(;i<300;i++)
        printf("%c",a[i]+'0');
    printf("\n");
    return 0;
}
