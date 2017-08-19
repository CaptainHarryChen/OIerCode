#include<cstdio>
#include<cstring>
const long long MOD=1000000007LL,MAXL=1005;
char str[MAXL];
//long long bit10[15];
int main()
{
	int T,len;
	long long ans,b0;
	//for(int i=1;i<10;i++)
		//bit10[i]=(bit10[i-1]*10)%MOD;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",str);
		len=strlen(str);
		ans=0LL;
		b0=1;
		for(int i=len-1,j;i>=0;i--)
		{
			if(str[i]==')')
			{
				long long x=0,y,b=1,z;
				sscanf(str+i-1,"%I64d",&y);
				for(j=i-5;j>=0&&str[j]!='(';j--)
				{
					x=(x+((str[j]-'0')*b)%MOD)%MOD;
					b=(b*10)%MOD;
				}
				z=x;
				for(int k=2;k<=y;k++)
					z=((z*b)%MOD+x)%MOD;
				ans=(ans+(z*b0)%MOD)%MOD;
				for(int k=1;k<=y;k++)
					b0=(b0*b)%MOD;
				i=j;
			}
			else
			{
				ans=(ans+((str[i]-'0')*b0)%MOD)%MOD;
				b0=(b0*10)%MOD;
			}
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
