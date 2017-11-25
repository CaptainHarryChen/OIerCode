#include<cstdio>
#include<algorithm>
const int MAXN=100005,MAXL=32;
using namespace std;

namespace Trie
{
	struct Node
	{
		int cnt;
		Node *son[2];
	};
	Node nodes[MAXN*MAXL],*rt,*cur;
	void Clear()
	{rt=NULL;cur=nodes+2;}
	void Insert(Node *&u,int a,int i)
	{
		if(u==NULL)
		{
			u=cur++;
			u->cnt=0;
			u->son[0]=u->son[1]=NULL;
		}
		if(i<0)
		{
			u->cnt++;
			return;
		}
		if(a&(1<<i))
			Insert(u->son[1],a,i-1);
		else
			Insert(u->son[0],a,i-1);
	}
	int Query(Node *u,int a,int i)
	{
		if(i<0)return 0;
		if(a&(1<<i))
		{
			if(u->son[0])
				return (1<<i)+Query(u->son[0],a,i-1);
			else
				return Query(u->son[1],a,i-1);
		}
		else
		{
			if(u->son[1])
				return (1<<i)+Query(u->son[1],a,i-1);
			return Query(u->son[0],a,i-1);
		}
	}
}

int A[MAXN];

int main()
{
	int T,n,sum,len,ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		len=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",A+i);
			int l=30,bit=1<<30;
			while(l>=0&&(A[i]&bit)==0)
				l--,bit>>=1;
			len=max(len,l);
		}
		sum=0;
		ans=0;
		Trie::Clear();
		Trie::Insert(Trie::rt,sum,len);
		for(int i=1;i<=n;i++)
		{
			sum^=A[i];
			ans=max(ans,Trie::Query(Trie::rt,sum,len));
			Trie::Insert(Trie::rt,sum,len);
		}
		printf("%d\n",ans);
	}
	return 0;
}
