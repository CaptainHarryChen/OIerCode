#include<cstdio>
#include<cstring>
const int MAXK=12;
bool use[MAXK];
char s[MAXK];
int pow10[MAXK];

int main()
{
	int N,K;
	scanf("%d%d",&N,&K);
	for(int i=1,x;i<=K;i++)
	{
		scanf("%d",&x);
		use[x]=true;
	}
	pow10[0]=1;
	for(int i=1;i<MAXK;i++)
		pow10[i]=pow10[i-1]*10;
	for(;;)
	{
		sprintf(s,"%d",N);
		int len=strlen(s);
		bool flag=true;
		for(int i=0;s[i];i++)
			if(use[s[i]-'0'])
			{
				N+=pow10[len-i-1];
				N-=N%pow10[len-i-1];
				flag=false;
				break;
			}
		if(flag)
			break;
	}
	printf("%d\n",N);
	
	return 0;
}
