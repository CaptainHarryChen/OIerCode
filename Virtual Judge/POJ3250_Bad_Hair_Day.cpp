#include<cstdio>
#include<iostream>
using namespace std;
const int MAXN=80005;

int n,h[MAXN];
int r[MAXN];
int stk[MAXN],tp;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",h+i);
	r[n]=n;
	stk[1]=n;tp=1;
	for(int i=n-1;i>=1;i--)
	{
		while(tp>0&&h[stk[tp]]<h[i])
			tp--;
		r[i]=tp==0?n:stk[tp]-1;
		stk[++tp]=i;
	}
	unsigned long long ans=0;
	for(int i=1;i<=n;i++)
		ans+=1LLU*(r[i]-i);
	cout<<ans<<endl;

	return 0;
}
