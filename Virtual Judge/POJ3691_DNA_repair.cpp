#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define charID(x) (x=='A'?0:(x=='G'?1:(x=='C'?2:3)))
const int MAXN=53,MAXL1=22,MAXL2=1005,MAXCHAR=4;

//dp[i][j]+ * -> dp[i+1][nxt[j]['A''G''C''T']]

struct Node
{
	int val;
	Node *son[MAXCHAR],*fail;
	void Clear()
	{memset(this,0,sizeof(Node));}
};

Node nodes[MAXN*MAXL1],*root=nodes,*ntop=nodes+1;
void Clear()
{
	root=nodes;
	root->Clear();
	ntop=nodes+1;
}
int ID(Node *u)
{return u-nodes;}
void Insert(const char *str)
{
	Node *u=root;
	for(int i=0;str[i];i++)
	{
		int c=charID(str[i]);
		if(u->son[c]==NULL)
		{
			u->son[c]=ntop++;
			u->son[c]->Clear();
		}
		u=u->son[c];
	}
	u->val=1;
}
void Build()
{
	static queue<Node*> Q;
	for(int i=0;i<MAXCHAR;i++)
		if(root->son[i])
		{
			root->son[i]->fail=root;
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
				Q.push(v);
				while(f&&f->son[i]==NULL)
					f=f->fail;
				if(f)
					v->fail=f->son[i];
				else
					v->fail=root;
				v->val|=v->fail->val;
			}
	}
}
Node *GetNext(Node *u,int c)
{
	while(u&&u->son[c]==NULL)
		u=u->fail;
	if(u)
		return u->son[c];
	return root;
}

char s[MAXL1],str[MAXL2];
int dp[MAXL2][MAXN*MAXL1];

int main()
{
	for(int test=1;;test++)
	{
		int n,m;
		scanf("%d",&n);
		if(n==0)
			break;
		Clear();
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s);
			Insert(s);
		}
		Build();
		scanf("%s",str+1);
		m=strlen(str+1);
		memset(dp,0x3F,sizeof dp);
		dp[0][0]=0;
		for(int i=0;i<m;i++)
			for(int j=0;nodes+j<ntop;j++)
				if(dp[i][j]<0x3F3F3F3F)
				{
					Node *u=nodes+j;
					for(int c=0;c<MAXCHAR;c++)
					{
						Node *v=GetNext(u,c);
						if(v->val)
							continue;
						dp[i+1][ID(v)]=min(dp[i+1][ID(v)],dp[i][j]+(c!=charID(str[i+1])));
					}
				}
		int ans=0x3F3F3F3F;
		for(int j=0;nodes+j<ntop;j++)
			ans=min(ans,dp[m][j]);
		if(ans==0x3F3F3F3F)
			ans=-1;
		printf("Case %d: %d\n",test,ans);
	}
	return 0;
}
