#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
#define MAXN 20005
char str[MAXN],temp[MAXN<<1];
int P[MAXN<<1],L[MAXN<<1],R[MAXN<<1];
int l,r;
void Manacher(const char *str)
{
	int n=strlen(str);
	temp[0]='@';
	for(int i=0;i<n;i++)
		temp[i*2+1]='#',temp[i*2+2]=str[i];
	temp[n*2+1]='#';temp[n*2+2]='$';
	int mx=0,po;
	for(int i=1;i<=n*2+1;i++)
	{
		if(mx>i)
			P[i]=min(mx-i,P[2*po-i]);
		else
			P[i]=1;
		while(temp[i-P[i]]==temp[i+P[i]])
			P[i]++;
		if(P[i]+i>mx)
		{mx=P[i]+i;po=i;}
		if(P[i]==i)L[l++]=i;
		if(P[i]==n*2+1-i+1)R[r++]=i;
	}
}
int main()
{
	int n,T,ll,rr,mid,i,j;
	bool flag;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",str);
		l=0;r=0;
		Manacher(str);
		n=strlen(str);
		flag=0;
		for(i=0;i<l&&!flag;i++)
		{
			if(P[L[i]]<=1)continue;
			for(j=0;j<r&&!flag;j++)
			{
				if(P[R[j]]<=1)continue;
				ll=L[i]+P[L[i]];
				rr=R[j]-P[R[j]];
				if(ll>rr)continue;
				mid=(ll+rr)>>1;
				if(P[mid]>1&&P[mid]>=rr-mid+1)
				{flag=1;break;}
			}
		}
		if(flag)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
