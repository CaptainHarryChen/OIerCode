#include<cstdio>
#include<cstring>
const int MAXN=30;

int C[MAXN][MAXN];
char str[MAXN];

int main()
{
	C[0][0]=1;
	for(int i=1;i<MAXN;i++)
	{
		C[i][0]=1;
		for(int j=1;j<MAXN;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	
	while(scanf("%s",str)!=EOF)
	{
		int n=strlen(str),ans=0;
		bool flag=true;
		for(int i=1;i<n;i++)
			if(str[i]<=str[i-1])
			{flag=false;break;}
		if(!flag)
		{
			puts("0");
			continue;
		}
		for(int i=0;i<n-1;i++)
			ans+=C[26][i+1];
		for(int i=0;i<n;i++)
			for(int j=(i==0?0:str[i-1]-'a'+1);j<str[i]-'a';j++)
				ans+=C[25-j][n-i-1];
		printf("%d\n",ans+1);
	}
	
	return 0;
}
