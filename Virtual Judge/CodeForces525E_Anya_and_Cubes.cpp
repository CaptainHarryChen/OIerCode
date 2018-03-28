#include<cstdio>
#include<cstring>
const int MAXN=30,MAXS=1594500,MAXHASH=999983;

class HashList
{
public:
	struct Node
	{
		long long id;
		long long val;
		Node *nxt;
	};
	static Node node[MAXS],*_new;
	Node *adj[MAXHASH];

	void Set(long long id,long long val)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
			{
				p->val=val;
				return;
			}
		_new->id=id;
		_new->val=val;
		_new->nxt=adj[pos];
		adj[pos]=_new++;
	}
	long long Get(long long id)
	{
		int pos=id%MAXHASH;
		for(Node *p=adj[pos];p;p=p->nxt)
			if(p->id==id)
				return p->val;
		return -1;
	}
};
HashList::Node HashList::node[MAXS],*HashList::_new=HashList::node;

HashList plan[MAXN];
int a[MAXN];
int pow3[MAXN];
long long fac[MAXN];

int main()
{
	fac[0]=1;
	for(int i=1;i<=18;i++)
		fac[i]=fac[i-1]*i;
	pow3[0]=1;
	for(int i=1;i<=13;i++)
		pow3[i]=pow3[i-1]*3;
	int n,k;
	long long S;
	scanf("%d%d%I64d",&n,&k,&S);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int s=0;s<pow3[n/2];s++)
	{
		int used=0,ts=s;
		long long sum=0;
		for(int i=0;i<n/2;i++,ts/=3)
		{
			if(ts%3==2)
			{
				if(a[i]>18)
				{
					sum=-1;
					break;
				}
				sum+=fac[a[i]];
				used++;
			}
			else if(ts%3==1)
				sum+=a[i];
		}
		if(sum==-1||used>k)continue;
		long long t=plan[used].Get(sum);
		if(t==-1)t=0;
		plan[used].Set(sum,t+1);
	}
	long long ans=0;
	for(int s=0;s<pow3[(n+1)/2];s++)
	{
		int used=0,ts=s;
		long long sum=0;
		for(int i=n/2;i<n;i++,ts/=3)
		{
			if(ts%3==2)
			{
				if(a[i]>18)
				{
					sum=-1;
					break;
				}
				sum+=fac[a[i]];
				used++;
			}
			else if(ts%3==1)
				sum+=a[i];
		}
		if(sum==-1||used>k||sum>S)continue;
		for(int i=0;i<=k-used;i++)
		{
			long long t=plan[i].Get(S-sum);
			if(t==-1)t=0;
			ans+=t;
		}
	}
	printf("%I64d\n",ans);
	
	return 0;
}
