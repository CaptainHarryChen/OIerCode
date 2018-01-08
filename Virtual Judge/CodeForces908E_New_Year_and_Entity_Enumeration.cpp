#include<cstdio>
#include<bitset>
using namespace std;
const int MAXM=1005,MAXN=55,MOD=1000000007;

typedef bitset<MAXM> Bint;

int bell[MAXM][MAXM];
void Init_Bell()
{
	bell[1][1]=1;
	for(int i=2;i<MAXM;i++)
	{
		bell[i][1]=bell[i-1][i-1];
		for(int j=2;j<=i;j++)
			bell[i][j]=(bell[i][j-1]+bell[i-1][j-1])%MOD;
	}
}

int n,m;
Bint A[MAXN*2];
int v[MAXM],tot;
bool vis[MAXM];

void Input()
{
	scanf("%d%d",&m,&n);
	for(int i=1,x;i<=n;i++)
		for(int j=0;j<m;j++)
		{
			scanf("%1d",&x);
			A[i][j]=x;
		}
	for(int i=1;i<=n;i++)
		A[n+i]=~A[i];
}
void Make_Partition()
{
	Bint t;
	for(int i=0;i<m;i++)
	{
		if(vis[i])continue;
		t.set();
		for(int j=1;j<=2*n;j++)
			if(A[j][i])
				t&=A[j];
		int cnt=0;
		for(int j=0;j<m;j++)
			if(t[j])
			{
				vis[j]=true;
				cnt++;
			}
		v[++tot]=cnt;
	}
}
int solve()
{
	int ans=1;
	for(int i=1;i<=tot;i++)
		ans=(1LL*ans*bell[v[i]][v[i]])%MOD;
	return ans;
}

int main()
{
	Input();
	Init_Bell();
	Make_Partition();
	printf("%d\n",solve());
	
	return 0;
}
