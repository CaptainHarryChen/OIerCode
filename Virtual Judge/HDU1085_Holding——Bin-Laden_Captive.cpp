#include<cstdio>
#include<cstring>
#define MAXN 8005
int c1[MAXN],c2[MAXN];
int main()
{
	int a,b,c,ans;
	while(~scanf("%d%d%d",&a,&b,&c))
	{
		if(!a&&!b&&!c)break;
		ans=a+2*b+5*c+1;
		for(int i=0;i<=a;i++)
			c1[i]=1;
		memset(c2,0,sizeof c2);
		for(int j=0;j<=a;j++)
			for(int k=0;k<=b;k++)
				c2[j+k*2]+=c1[j];
		memcpy(c1,c2,sizeof c1);
		for(int j=0;j<=a+2*b;j++)
			for(int k=0;k<=c;k++)
				c2[j+k*5]+=c1[j];
		for(int i=0;i<=a+2*b+5*c;i++)
			if(!c2[i])
			{ans=i;break;}
		printf("%d\n",ans);
	}
	return 0;
}
