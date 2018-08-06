#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=205,MAXK=1005,MAXCHAR=26;

struct Node
{
	bool vis;
	int val;
	Node *son[MAXCHAR],*fail;
};

Node nodes[MAXN],*root,*ntop;
int pos[MAXN][MAXCHAR];

void Init()
{
	memset(nodes,0,sizeof nodes);
	root=nodes;
	ntop=nodes+1;
}
void Insert(const char *str,int val)
{
	Node *u=root;
	for(int i=0;str[i];i++)
	{
		int c=str[i]-'a';
		if(u->son[c]==NULL)
			u->son[c]=ntop++;
		u=u->son[c];
	}
	u->val+=val;
}
void Build()
{
	static queue<Node*> Q;
	for(int i=0;i<MAXCHAR;i++)
		if(root->son[i])
		{
			root->son[i]->fail=root;
			pos[0][i]=root->son[i]-nodes;
			Q.push(root->son[i]);
		}
	while(!Q.empty())
	{
		Node *u=Q.front();
		Q.pop();
		for(int i=0;i<MAXCHAR;i++)
			if(u->son[i])
			{
				Node *v=u->son[i],*f=u->fail;
				pos[u-nodes][i]=v-nodes;
				Q.push(v);
				while(f!=root&&f->son[i]==NULL)
					f=f->fail;
				if(f->son[i])
					v->fail=f->son[i];
				else
					v->fail=root;
				v->val+=v->fail->val;
			}
			else
			{
				Node *tmp=u->fail;
				while(tmp&&tmp->son[i]==NULL)
					tmp=tmp->fail;
				if(tmp)
					pos[u-nodes][i]=tmp->son[i]-nodes;
				else
					pos[u-nodes][i]=0;
			}
	}
}

struct Matrix
{
	int siz;
	long long A[MAXN][MAXN];
	Matrix(int _siz=0)
	{
		siz=_siz;
		for(int i=0;i<siz;i++)
			for(int j=0;j<siz;j++)
				A[i][j]=-1;
	}
	long long* operator [] (int i)
	{return A[i];}
	Matrix operator * (Matrix &B)const
	{
		Matrix ret(siz);
		for(int i=0;i<siz;i++)
			for(int j=0;j<siz;j++)
				for(int k=0;k<siz;k++)
					if(A[i][k]!=-1&&B[k][j]!=-1)
						ret[i][j]=max(ret[i][j],A[i][k]+B[k][j]);
		return ret;
	}
	void Debug()
	{
		static int ti=1;
		printf("Debug %d,the %dth:\n",(int)this,ti++);
		for(int i=0;i<siz;i++)
		{
			for(int j=0;j<siz;j++)
				printf("%3I64d",A[i][j]);
			puts("");
		}
		printf("Debug end\n");
	}
};

Matrix Pow(Matrix &A,long long B)
{
	Matrix ret=A;
	B--;
	while(B)
	{
		if(B&1LL)
			ret=ret*A;
		//ret.Debug();
		//B--;
		B>>=1LL;
		A=A*A;
	}
	return ret;
}

char s[MAXN];
int A[MAXN];

Matrix f;

int main()
{
	Init();
	int N;
	long long l;
	scanf("%d%I64d",&N,&l);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=N;i++)
	{
		scanf("%s",s);
		Insert(s,A[i]);
	}
	Build();
	
	int m=ntop-nodes;
	f=Matrix(m);
	for(int i=0;i<m;i++)
		for(int c=0;c<MAXCHAR;c++)
		{
			if(f[i][pos[i][c]]==-1)
				f[i][pos[i][c]]=0;
			f[i][pos[i][c]]+=nodes[pos[i][c]].val;
		}
	//f.Debug();
	f=Pow(f,l);
	long long ans=0;
	for(int i=0;i<m;i++)
		ans=max(ans,f[0][i]);
	printf("%I64d\n",ans);
	
	return 0;
}
