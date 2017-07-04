#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using std::swap;
using std::abs;
using std::min;
#define MAXN 2005
namespace LeftistTree
{
	struct Node
	{
		int x,dis;
		Node *son[2];
		Node(){son[0]=son[1]=NULL;x=dis=0;}
		Node(int _x){son[0]=son[1]=NULL;x=_x;dis=0;}
	};
	Node *Merge(Node *r1,Node *r2)
	{
		if(r1==NULL)return r2;
		if(r2==NULL)return r1;
		if(r1->x>r2->x)swap(r1,r2);
		r1->son[1]=Merge(r1->son[1],r2);
		if(r1->son[0]==NULL||r1->son[1]->dis>r1->son[0]->dis)
			swap(r1->son[0],r1->son[1]);
		if(r1->son[1]==NULL)r1->dis=0;
		else r1->dis=r1->son[1]->dis+1;
		return r1;
	}
	void Insert(Node *&T,int x)
	{
		Node *u=new Node(x);
		if(T==NULL)T=u;
		else T=Merge(T,u);
	}
	void Delete(Node *&T)
	{T=Merge(T->son[0],T->son[1]);}
}
int A[MAXN];
using namespace LeftistTree;
Node *S[MAXN];
int len[MAXN];
int main()
{
	int n,m,s1,s2;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	m=1;
	Insert(S[m],-A[1]);
	len[m]=1;
	for(int i=2;i<=n;i++)
	{
		if(-A[i]<=S[m]->x)
		{
			Insert(S[++m],-A[i]);
			if(len[m]%2==1)Delete(S[m]);
			len[m]++;
		}
		else
		{
			Insert(S[m],-A[i]);
			if(len[m]%2==1)Delete(S[m]);
			len[m]++;
		}
		while(m>1&&S[m]->x>S[m-1]->x)
		{
			S[--m]=Merge(S[m],S[m+1]);
			if(len[m]%2==1&&len[m+1]%2==1)Delete(S[m]);
			len[m]=len[m]+len[m+1];
			S[m+1]=NULL;len[m+1]=0;
		}
	}
	s1=0;
	for(int i=1,j=1,s=len[j];i<=n;i++)
	{
		if(i>s){j++;s+=len[j];}
		s1+=abs(A[i]+S[j]->x);
	}
	memset(S,0,sizeof S);
	memset(len,0,sizeof len);
	m=1;
	Insert(S[m],-A[n]);
	len[m]=1;
	for(int i=n-1;i>0;i--)
	{
		if(-A[i]<=S[m]->x)
		{
			Insert(S[++m],-A[i]);
			if(len[m]%2==1)Delete(S[m]);
			len[m]++;
		}
		else
		{
			Insert(S[m],-A[i]);
			if(len[m]%2==1)Delete(S[m]);
			len[m]++;
		}
		while(m>1&&S[m]->x>S[m-1]->x)
		{
			S[--m]=Merge(S[m],S[m+1]);
			if(len[m]%2==1&&len[m+1]%2==1)Delete(S[m]);
			len[m]=len[m]+len[m+1];
			S[m+1]=NULL;len[m+1]=0;
		}
	}
	s2=0;
	for(int i=n,j=1,s=n-len[j]+1;i>0;i--)
	{
		if(i<s){j++;s-=len[j];}
		s2+=abs(A[i]+S[j]->x);
	}
	printf("%d\n",min(s1,s2));
	return 0;
}
