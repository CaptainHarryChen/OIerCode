#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s[100][1005],s2[1000],e;
int main()
{
	int n;
	scanf("%d%c",&n,&e);
	for(int i=0;i<n;i++)
		gets(s[i]);
	for(int i=0,len=strlen(s[i]);i<n;i++,len=strlen(s[i]))
	{
		for(int j=0,len2=strlen(s2);j<len;j++,len2=strlen(s2))
		{
			if(s[i][j]=='A')
				strcat(s2,"2");
			else if(s[i][j]=='B')
				strcat(s2,"22");
			else if(s[i][j]=='C')
				strcat(s2,"222");
			else if(s[i][j]=='D')
				strcat(s2,"3");
			else if(s[i][j]=='E')
				strcat(s2,"33");
			else if(s[i][j]=='F')
				strcat(s2,"333");
			else if(s[i][j]=='G')
				strcat(s2,"4");
			else if(s[i][j]=='H')
				strcat(s2,"44");
			else if(s[i][j]=='I')
				strcat(s2,"444");
			else if(s[i][j]=='J')
				strcat(s2,"5");
			else if(s[i][j]=='K')
				strcat(s2,"55");
			else if(s[i][j]=='L')
				strcat(s2,"555");
			else if(s[i][j]=='M')
				strcat(s2,"6");
			else if(s[i][j]=='N')
				strcat(s2,"66");
			else if(s[i][j]=='O')
				strcat(s2,"666");
			else if(s[i][j]=='P')
				strcat(s2,"7");
			else if(s[i][j]=='Q')
				strcat(s2,"77");
			else if(s[i][j]=='R')
				strcat(s2,"777");
			else if(s[i][j]=='S')
				strcat(s2,"7777");
			else if(s[i][j]=='T')
				strcat(s2,"8");
			else if(s[i][j]=='U')
				strcat(s2,"88");
			else if(s[i][j]=='V')
				strcat(s2,"888");
			else if(s[i][j]=='W')
				strcat(s2,"9");
			else if(s[i][j]=='X')
				strcat(s2,"99");
			else if(s[i][j]=='Y')
				strcat(s2,"999");
			else if(s[i][j]=='Z')
				strcat(s2,"9999");
			else if(s[i][j]==' ')
				strcat(s2,"0");
			int len3=strlen(s2);
			if(s2[len2-1]==s2[len3-1])
			{
				char s3[50]={0};
				for(int k=len2,a=0;k<len3;k++)
				{s3[a++]=s2[k];s2[k]=0;}
				s2[len2]=' ';
				strcat(s2,s3);
			}
		}
		puts(s2);
		memset(s2, 0,  sizeof(s2));
	}
	return 0;
}
