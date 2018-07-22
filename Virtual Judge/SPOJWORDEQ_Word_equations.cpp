#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=10005,MAXC=30;

struct bign {
    static const int BASE = 10;
    static const int WIDTH = 1;
    vector<int> s;
    bign (long long num = 0) 
	{
		s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        }
        while(num > 0);
	}
    void clear_prefix_zero() {
        while(s.size() != 1 && s.back() == 0)
            s.pop_back();
    }
    bign operator * (const bign& b) const {
        bign c;
        c.s.clear();
        c.s.resize(s.size() + b.s.size() + 1);
        for(int i = 0; i < (int)s.size(); i++)
            for(int j = 0; j < (int)b.s.size(); j++) {
                int k = i + j;
                int x = s[i] * b.s[j] + c.s[k];
                int g = x / BASE;
                x %= BASE;
                c.s[k + 1] += g;
                c.s[k] = x;
            }
        c.clear_prefix_zero();
        return c;
    }
};

bool vis[MAXN];
int fa[MAXN];
int Root(int u)
{
	if(fa[u]==-1)
		return u;
	return fa[u]=Root(fa[u]);
}
bool Union(int u,int v)
{
	int r1=Root(u),r2=Root(v);
	if(r1==r2)
		return true;
	if(r1<2&&r2<2&&r1!=r2)
		return false;
	
	if(r1<2)
		swap(r1,r2);
	fa[r1]=r2;
	return true;
}

bign ans;
int len[MAXC],id[MAXC];
int A[MAXN],B[MAXN];
char s1[MAXN],s2[MAXN];

int main()
{
	int T,k,n,m;
	scanf("%d",&T);
	while(T--)
	{
		memset(fa,-1,sizeof fa);
		memset(vis,0,sizeof vis);
		memset(id,0,sizeof id);
		
		scanf("%d",&k);
		for(int i=0;i<k;i++)
			scanf("%d",&len[i]);
		scanf("%d%s%d%s",&n,s1,&m,s2);
		
		int cur=2;
		for(int i=0;i<k;i++)
			id[i]=cur,cur+=len[i];
		
		int len0=cur-1,len1=0,len2=0;
		bool flag=true;
		
		for(int i=0;i<n;i++)
		{
			if(s1[i]=='0'||s1[i]=='1')
				A[++len1]=s1[i]-'0';
			else
				for(int j=0;j<len[s1[i]-'a'];j++)
					A[++len1]=id[s1[i]-'a']+j;
		}
		
		for(int i=0;i<m;i++)
		{
			if(s2[i]=='0'||s2[i]=='1')
				B[++len2]=s2[i]-'0';
			else
				for(int j=0;j<len[s2[i]-'a'];j++)
					B[++len2]=id[s2[i]-'a']+j;
		}
		
		if(len1!=len2)
			flag=false;
			
		for(int i=1;i<=len1&&flag;i++)
			if(!Union(A[i],B[i]))
				flag=false;
		
		if(!flag)
			puts("0");
		else
		{
			int cnt=0;
			for(int i=2;i<=len0;i++)
			{
				int r=Root(i);
				if(r>=2&&!vis[r])
					cnt++,vis[r]=true;
			}
			ans=bign(1);
			while(cnt--)
				ans=ans*bign(2);
			for(int i=ans.s.size()-1;i>=0;i--)
				printf("%d",ans.s[i]);
			puts("");
		}
	}
	return 0;
}
