#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
char s[1500][300],t[1500][300],s1[5000],s2[5000];
int n,a=1,aa,b=1;
bool f[1500][300];
void part(char *s,int len,char a[][300],int &cnt)
{
	int n[5000]={0};
	int i;
	cnt=1;
	for(i=0;i<len;i++)
	{
		if(isalpha(s[i]))
			a[cnt][++n[cnt]]=s[i];
		else if(s[i]=='.')
		{
			cnt++;
			continue;
		}
		else if(!s[i])
			return;
		else if(s[i]=='*')
			a[cnt][1]='$';
		else if(s[i]=='?')
		{
			a[cnt][1]='@';
			a[++cnt][1]='#';
			a[++cnt][1]='#';
		}
		else if(s[i]=='!')
		{
			a[cnt][1]='@';
			a[++cnt][1]='@';
			a[++cnt][1]='$';
		}
	}
}
void dp()
{
	for(int x=1;x<=a;x++)
		for(int y=1;y<=b;y++)
			if(s[x][1]>='a'&&s[x][1]<='z'&&t[y][1]>='a'&&t[y][1]<='z')
				f[x][y]=f[x-1][y-1]&&(strcmp(s[x]+1,t[y]+1)==0);
			else
			{
				if(s[x][1]=='@'||t[y][1]=='@')
					f[x][y]=f[x-1][y-1];
				if(s[x][1]=='#'||t[y][1]=='$')
					f[x][y]=f[x][y]||f[x-1][y-1]||f[x-1][y];
				if(s[x][1]=='$'||t[y][1]=='#')
					f[x][y]=f[x][y]||f[x-1][y-1]||f[x][y-1];
			}
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		memset(s,0,sizeof(s));
		memset(t,0,sizeof(t));
		memset(f,0,sizeof(f));
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		f[0][0]=1;
		scanf("%s%s",s1,s2);
		int len1=strlen(s1),len2=strlen(s2);
		part(s1,len1,s,a);
		part(s2,len2,t,b);
		dp();
		if(f[a][b])
			puts("YES");
		else
			puts("NO");
	}
}