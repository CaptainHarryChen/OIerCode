#include<cstdio>
#include<algorithm>
const int MAXN=100005,MAXL=23;
using namespace std;

long long ans;
int A[MAXN];

namespace Trie
{
	struct Node
	{
		int cnt,sum;
		Node *son[2];
	};
	Node nodes[MAXN*MAXL],*rt,*cur,*null;
	void Clear()
	{
		null=nodes;
		null->cnt=null->sum=0;
		null->son[0]=null->son[1]=null;
		rt=null;
		cur=nodes+2;
	}
	void Insert(Node *&u,int a,int i)
	{
		if(u==null)
		{
			u=cur++;
			u->cnt=u->sum=0;
			u->son[0]=u->son[1]=null;
		}
		if(i<0)
		{
			u->cnt++;
			u->sum++;
			return;
		}
		if(a&(1<<i))
			Insert(u->son[1],a,i-1);
		else
			Insert(u->son[0],a,i-1);
		u->sum=u->son[0]->sum+u->son[1]->sum;
	}
	void Calc(Node *u,int a,int k,int i)
	{
		if(u==null)return;
		if(a&(1<<i))
		{
			if((k>>i)&1)
				ans+=1LL*u->son[1]->sum;
			Calc(u->son[((k>>i)&1)^1],a,k,i-1);
		}
		else
		{
			if((k>>i)&1)
				ans+=1LL*u->son[0]->sum;
			Calc(u->son[(k>>i)&1],a,k,i-1);
		}
	}
}

int main()
{
	int T,n,k,sum,len;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		len=0;
		int l=30,bit=1<<30;
		while(l>=0&&(k&bit)==0)
			l--,bit>>=1;
		len=max(len,l);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",A+i);
			l=30,bit=1<<30;
			while(l>=0&&(A[i]&bit)==0)
				l--,bit>>=1;
			len=max(len,l);
		}
		sum=0;
		ans=0LL;
		Trie::Clear();
		Trie::Insert(Trie::rt,sum,len);
		for(int i=1;i<=n;i++)
		{
			sum^=A[i];
			Trie::Calc(Trie::rt,sum,k,len);
			Trie::Insert(Trie::rt,sum,len);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
