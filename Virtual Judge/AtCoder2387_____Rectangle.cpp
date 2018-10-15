#include<cstdio>
const int MAXN=505;

int H,W,h,w;
int arr[MAXN][MAXN];

int main()
{
	scanf("%d%d%d%d",&H,&W,&h,&w);
	if(h==1&&w==1)
	{
		puts("No");
		return 0;
	}
	long long sum=0;
	int k=999999999/(h*w-1);
	{
		sum=0;
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
			{
				if(i%h==0&&j%w==0)
					arr[i][j]=-k*(h*w-1)-1;
				else
					arr[i][j]=k;
				sum+=arr[i][j];
			}
		if(sum>0)
		{
			puts("Yes");
			for(int i=1;i<=H;i++)
			{
				for(int j=1;j<=W;j++)
					printf("%d ",arr[i][j]);
				puts("");
			}
			return 0;
		}
	}
	puts("No");
	
	return 0;
}
