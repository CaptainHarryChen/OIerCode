#include<cstdio>
#include<cstring>
int main()
{
	int a[6],b[6];
	while(1)
	{
		for(int i=0;i<6;i++)
			scanf("%d",a+i);
		if(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]==0)
			break;
		int ans=0;
		memset(b,0,sizeof b);
		ans+=a[5];
		ans+=a[4];
		b[0]+=a[4]*11;
		ans+=a[3];
		b[1]+=a[3]*5;
		ans+=a[2]/4;
		if(a[2]%4==1)
		{
			b[1]+=5;
			b[0]+=7;
			ans++;
		}
		if(a[2]%4==2)
		{
			b[1]+=3;
			b[0]+=6;
			ans++;
		}
		if(a[2]%4==3)
		{
			b[1]+=1;
			b[0]+=5;
			ans++;
		}
		if(a[1]<=b[1])
			b[1]-=a[1];
		else
		{
			a[1]-=b[1];
			b[1]=0;
			ans+=a[1]/9;
			if(a[1]%9)
			{
				b[0]+=36-4*(a[1]%9);
				ans++;
			}
		}
		if(a[0]>b[0]+b[1]*4)
		{
			a[0]-=b[0]+b[1]*4;
			ans+=a[0]/36;
			if(a[0]%36)
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
