#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;

int n,m;
int A[MAXN],B[MAXN];
int a[MAXN],b[MAXN];
int ans[MAXN][MAXN];

bool solve(int bit)
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++)
	{
		if(A[i]&bit)
			a[i]=1,cnt1++;
		else
			a[i]=0;
	}
	for(int j=1;j<=m;j++)
	{
		if(B[j]&bit)
			b[j]=1,cnt2++;
		else
			b[j]=0;
	}
	for(int i=1;i<=n;i++)
		if(a[i])
		{
			if(cnt2)
			{
				for(int j=1;j<=m;j++)
					if(b[j])
					{
						ans[i][j]|=bit;
						a[i]=b[j]=0;
						cnt1--;cnt2--;
						break;
					}
			}
			else
			{
				int k;
				for(k=i+1;k<=n&&!a[k];k++);
				if(k>n)return false;
				ans[i][1]|=bit;ans[k][1]|=bit;
				a[i]=a[k]=0;
				cnt1-=2;
				i=k;
			}
		}
	if(cnt1)
		return false;
	for(int j=1;j<=m;j++)
		if(b[j])
		{
			int k;
			for(k=j+1;k<=m&&!b[k];k++);
			if(k>m)return false;
			bool flag=false;
			for(int p=1;p<=n;p++)
				if((ans[p][j]&bit)==0)
				{ans[p][j]|=bit;flag=true;break;}
			if(!flag)return false;
			flag=false;
			for(int p=1;p<=n;p++)
				if((ans[p][k]&bit)==0)
				{ans[p][k]|=bit;flag=true;break;}
			if(!flag)return false;
			cnt2-=2;
			b[j]=b[k]=0;
		}
	
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int j=1;j<=m;j++)
		scanf("%d",&B[j]);
	
	for(int bit=1;bit>0;bit<<=1)
		if(!solve(bit))
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);
		puts("");
	}
	
	return 0;
}
