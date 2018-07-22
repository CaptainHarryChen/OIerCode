#include<cstdio>
#include<cstring>
const int MAXN=100005,MAXS=1<<6;

char S[MAXN];
int st[MAXN],cnt[MAXN][MAXS+10],num[7],tmp[MAXS+10];

int main()
{
	int n,m;
	scanf("%s%d",S+1,&m);
	n=strlen(S+1);
	for(int i=1;i<=n;i++)
		num[S[i]-'a']++;
	for(int i=1,p;i<=m;i++)
	{
		char s[10];
		scanf("%d%s",&p,s);
		for(int j=0;s[j];j++)
			st[p]|=(1<<(s[j]-'a'));
	}
	for(int i=1;i<=n;i++)
		if(st[i]==0)
			st[i]=MAXS-1;
	for(int i=n;i>=1;i--)
		for(int j=0;j<MAXS;j++)
		{
			if((st[i]&j)==st[i])
				tmp[j]++;
			cnt[i][j]=tmp[j];
		}
	for(int i=1;i<=n;i++)
	{
		bool possible=false;
		for(int c=0;c<6;c++)
		{
			if((st[i]&(1<<c))==0||num[c]==0)
				continue;
			num[c]--;
			bool flag=true;
			for(int s=0;s<MAXS&&flag;s++)
			{
				int sum=0;
				for(int j=0;j<6;j++)
					if(s&(1<<j))
						sum+=num[j];
				flag=(sum>=cnt[i+1][s]);
			}
			if(flag)
			{
				possible=true;
				S[i]=c+'a';
				break;
			}
			num[c]++;
		}
		if(!possible)  
		{
			puts("Impossible");
			return 0;
		}
	}
	
	puts(S+1);
	
	return 0;
}
