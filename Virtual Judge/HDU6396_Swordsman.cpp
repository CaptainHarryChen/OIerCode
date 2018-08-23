#include<cstdio> 
#include<cstring> 
#include<algorithm> 
#include<vector>
#include<queue>
const int MAXN=100005,MAXK=5,INF=0x3F3F3F3F; 
using namespace std; 

inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int _read(){
    char ch=nc();int sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
    return sum;
}

int N,K,tt;
int a[MAXN][MAXK],b[MAXN][MAXK],hp[MAXN];
int pos[MAXK][MAXN];
int now[MAXK],id[MAXK];
queue<int> Q;

bool cmp(int x,int y)
{
	return a[x][tt]<a[y][tt];
}

int main() 
{
	//freopen("in.txt","r",stdin);
	int test;
	test=_read();
    while(test--) 
    { 
		N=_read();K=_read();
		for(int j=0;j<K;j++)
			now[j]=_read();
        for(int i=1;i<=N;i++)
		{
			for(int j=0;j<K;j++) 
				a[i][j]=_read();
			for(int j=0;j<K;j++)
				b[i][j]=_read();
			hp[i]=K;
		}
		for(int j=0;j<K;j++)
		{
			for(int i=1;i<=N;i++)
				pos[j][i]=i;
			tt=j;
			sort(pos[j]+1,pos[j]+N+1,cmp);
			id[j]=1;
			while(id[j]<=N&&a[pos[j][id[j]]][j]<=now[j])
			{
				hp[pos[j][id[j]]]--;
				if(hp[pos[j][id[j]]]==0)
					Q.push(pos[j][id[j]]);
				id[j]++;
			}
		}
		
		int ans=0;
		while(!Q.empty())
		{
			int u=Q.front();
			Q.pop();
			ans++;
			for(int j=0;j<K;j++)
				now[j]+=b[u][j];
			for(int j=0;j<K;j++)
				while(id[j]<=N&&a[pos[j][id[j]]][j]<=now[j])
				{
					hp[pos[j][id[j]]]--;
					if(hp[pos[j][id[j]]]==0)
						Q.push(pos[j][id[j]]);
					id[j]++;
				}
		}
		
		printf("%d\n",ans);
		for(int i=0;i<K;i++)
			printf("%d%c",now[i]," \n"[(i==K-1)]);
    }
    return 0; 
}
