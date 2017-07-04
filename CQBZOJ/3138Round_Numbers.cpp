#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int S,T,ans,C[35][35];
int getlength(long long n)
{
	for(long long i=1,j=0;;i<<=1,j++)
		if(n<=(i-1))
			return (int)j;
}
void get_C()
{
	for(int i=0;i<=32;i++)
		for(int j=0;j<=i;j++)
			if(!j||i==j)
				C[i][j]=1;
			else
				C[i][j]=C[i-1][j-1]+C[i-1][j];
}
int count(int X)
{
	if(X==0)return 0;
	int len=getlength(X),ans=0,zero_cnt=0;
	for(int i=1;i<len-1;i++)
		for(int j=i/2+1;j<=i;j++)
			ans+=C[i][j];
	for(int i=1<<(len-2),k=len-1;k>=1;i>>=1,k--)
		if(X&i)
		{
			for(int j=(len+1)/2-(zero_cnt+1);j<=k-1;j++)
				ans+=C[k-1][j];
		}
		else
			zero_cnt++;
	return ans;
}
int main()
{
	get_C();
	scanf("%d%d",&S,&T);
	ans=count(T+1)-count(S);
	printf("%d\n",ans);
	return 0;
}
