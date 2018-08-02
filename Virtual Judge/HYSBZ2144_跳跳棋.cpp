#include<cstdio>
#include<algorithm>
using namespace std;
typedef pair<int,int> node;

int getfa(node &u,int lev)
{
	int tmp=lev,a=u.first,b=u.second;
	while(lev)
	{
		int k=0;
		if(a==b)
		{
			u=node(a,b);
			return tmp-lev;
		}
		if(a<b)
		{
			k=min((b-1)/a,lev);
			b-=k*a;
		}
		else
		{
			k=min((a-1)/b,lev);
			a-=k*b;
		}
		lev-=k;
	}
	u=node(a,b);
	return tmp-lev;
}

int main()
{
	int a[4],b[4];
	scanf("%d%d%d%d%d%d",&a[0],&a[1],&a[2],&b[0],&b[1],&b[2]);
	sort(a,a+3);
	sort(b,b+3);
	node s(a[1]-a[0],a[2]-a[1]),t(b[1]-b[0],b[2]-b[1]);
	int len1=getfa(s,0x7FFFFFFF),len2=getfa(t,0x7FFFFFFF);
	if(s!=t)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	s=node(a[1]-a[0],a[2]-a[1]);
	t=node(b[1]-b[0],b[2]-b[1]);
	if(len1>len2)
	{
		swap(s,t);
		swap(len1,len2);
	}
	int ans=len2-len1;
	getfa(t,len2-len1);
	int l=0,r=len1;
	while(l<r)
	{
		int mid=(l+r)/2;
		node x=s,y=t;
		getfa(x,mid);
		getfa(y,mid);
		if(x==y)
			r=mid;
		else
			l=mid+1;
	}
	ans+=l*2;
	printf("%d\n",ans);
	
	return 0;
}
