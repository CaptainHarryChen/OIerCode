#include<cstdio>
#include<cmath>
#include<cstring>
const int MAXHASH=100000;

template<class T>
bool Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return true;
		}
	}
	return false;
}

namespace Hash
{
	struct Node
	{
		long long id;
		int val;
		Node *nxt;
	}*adj[MAXHASH+10],node[MAXHASH+10],*ncnt=node;
	void clear()
	{memset(adj,0,sizeof adj);ncnt=node;}
	void add(long long pos,int val)
	{
		ncnt->id=pos;
		ncnt->val=val;
		ncnt->nxt=adj[pos%MAXHASH];
		adj[pos%MAXHASH]=ncnt;
		ncnt++;
	}
	int get(long long pos)
	{
		for(Node *p=adj[pos%MAXHASH];p;p=p->nxt)
			if(p->id==pos)
				return p->val;
		return -1;
	}
};

long long pow_mod(long long a,long long b,long long p)
{
	long long res=1LL;
	for(;b;b>>=1LL,a=(a*a)%p)
		if(b&1LL)
			res=(res*a)%p;
	return res;
}

long long work(long long P,long long B,long long N)
{
	long long m,v,e=1,i;
	m=ceil(sqrt(P+0.5));
	v=pow_mod(B,P-m-1,P);
	Hash::clear();
	Hash::add(1,0);
	for(i=1;i<m;i++)
	{
		e=(e*B)%P;
		if(Hash::get(e)==-1)
			Hash::add(e,i);
	}
	for(i=0;i<m;i++)
	{
		int t=Hash::get(N);
		if(t!=-1)
			return i*m+t;
		N=(N*v)%P;
	}
	return -1;
}

int main()
{
	long long P,B,N;
	while(Read(P))
	{
		Read(B);Read(N);
		long long ans=work(P,B,N);
		if(ans==-1)
			printf("no solution\n");
        else
			printf("%I64d\n",ans);
	}
	return 0;
}
