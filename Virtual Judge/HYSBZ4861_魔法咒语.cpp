#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=55,MAXL=105,MAXCHAR=26,MAXNODE=305,MOD=1000000007;

struct Node
{
    Node *son[MAXCHAR],*fail;
    int id;
    bool ed;
};

struct ACautomation
{
    Node nodes[MAXNODE],*root,*nodes_it;

    Node *NewNode()
    {
        memset(nodes_it,0,sizeof(Node));
        return nodes_it++;
    }
    void Clear()
    {
        nodes_it=nodes;
        root=NewNode();
    }
    void Insert(const char *s)
    {
        Node *u=root;
        for(int i=0;s[i];i++)
        {
            Node *&v=u->son[s[i]-'a'];
            if(v==NULL)
            {
                v=NewNode();
                v->id=v-nodes;
                //printf("(%d %d %c)\n",u-nodes,v-nodes,s[i]);
            }
            u=v;
        }
        u->ed=true;
    }
    void BuildFail()
    {
        static Node* Q[MAXNODE];
        static int l,r;
        l=1,r=1;Q[1]=root;
        while(l<=r)
        {
            Node *u=Q[l++];
            for(int c=0;c<MAXCHAR;c++)
                if(u->son[c])
                {
                    Node *v=u->son[c],*f=u->fail;
                    while(f&&f->son[c]==NULL)
                        f=f->fail;
                    if(f)
                        v->fail=f->son[c];
                    else
                        v->fail=root;
                    //printf("[%d %d]\n",v-nodes,v->fail-nodes);
                    v->ed|=v->fail->ed;
                    Q[++r]=v;
                }
        }
    }
};

struct Matrix
{
	int h,w;
	int a[MAXNODE][MAXNODE];
	Matrix(){h=w=0;}
	void Clear(int _h,int _w)
	{
		h=_h;
		w=_w;
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
				a[i][j]=0;
	}
	Matrix(int h,int w)
	{Clear(h,w);}

	int *operator [] (int i)
	{return a[i];}
	const int *operator [] (int i)const
	{return a[i];}

	Matrix operator * (const Matrix &t)const
	{
		Matrix res(0,0);
		int l=t.h;
		if(l!=this->w)
			return res;
		int h=this->h;
		int w=t.w;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			for(int k=0;k<l;k++)
				if(a[i][k])
					for(int j=0;j<w;j++)
						res[i][j]=(res[i][j]+(1LL*a[i][k]*t.a[k][j])%MOD)%MOD;
		return res;
	}
	Matrix pow(int b)const
	{
		Matrix res(0,0);
		if(h!=w)
			return res;
		Matrix d=*this;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			res.a[i][i]=1;
		while(b)
		{
			if(b&1)
				res=res*d;
			d=d*d;
			b>>=1;
		}
		return res;
	}
};

ACautomation AC;
int N,M,L,C;

int len1[MAXN],len2[MAXN];
char s1[MAXN][MAXL],s2[MAXN][MAXL];
int dp[MAXL][MAXNODE];

Matrix f,A;

int main()
{
    scanf("%d%d%d",&N,&M,&L);
    for(int i=1;i<=N;i++)
    {
        scanf("%s",s1[i]+1);
        len1[i]=strlen(s1[i]+1);
    }
    AC.Clear();
    for(int i=1;i<=M;i++)
    {
        scanf("%s",s2[i]+1);
        AC.Insert(s2[i]+1);
        len2[i]=strlen(s2[i]+1);
    }
    AC.BuildFail();
    C=AC.nodes_it-AC.nodes;

    if(L<=100)
    {
        dp[0][0]=1;
        for(int i=0;i<L;i++)
            for(int j=0;j<C;j++)
                if(dp[i][j])
                {
                    //printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
                    for(int k=1;k<=N;k++)
                        if(i+len1[k]<=L)
                        {
                            bool flag=true;
                            Node *u=AC.nodes+j;
                            for(int p=1;p<=len1[k]&&flag;p++)
                            {
                                int c=s1[k][p]-'a';
                                Node *v=u;
                                while(v!=AC.root&&v->son[c]==NULL)
                                    v=v->fail;
                                if(v->son[c])
                                    u=v->son[c];
                                else
                                    u=v;
                                if(u->ed)
                                    flag=false;
                            }
                            if(flag)
                                (dp[i+len1[k]][u->id]+=dp[i][j])%=MOD;
                        }
                }
        int ans=0;
        for(int j=0;j<C;j++)
            (ans+=dp[L][j])%=MOD;
        printf("%d\n",ans);
    }
    else
    {
        f.Clear(C*2,C*2);
        A.Clear(C*2,C*2);
        for(int j=0;j<C;j++)
            f[j+C][j]=1;
        A[0][C]=1;
        for(int j=0;j<C;j++)
            for(int k=1;k<=N;k++)
            {
                bool flag=true;
                Node *u=AC.nodes+j;
                for(int p=1;p<=len1[k]&&flag;p++)
                {
                    int c=s1[k][p]-'a';
                    Node *v=u;
                    while(v!=AC.root&&v->son[c]==NULL)
                        v=v->fail;
                    if(v->son[c])
                        u=v->son[c];
                    else
                        u=v;
                    if(u->ed)
                        flag=false;
                }
                if(flag)
                {
                    if(len1[k]==1)
                        f[j+C][u->id+C]++;
                    else
                        f[j][u->id+C]++;
                }
            }
        A=A*f;
        f=f.pow(L);
        A=A*f;
        int ans=0;
        for(int j=0;j<C;j++)
            ans=(ans+A[0][j])%MOD;
        printf("%d\n",ans);
    }

    return 0;
}
