#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=105,MAXLEN=10005,MAXM=1000005;
const long long MOD[2]={67891LL,1000000207LL};

int n,m;
char str[MAXLEN];
long long A[MAXN][2];
bool can[MAXM];
vector<int> ans;

void module(long long res[2])
{
	for(int k=0;k<2;k++)
	{
		bool flag=false;
		res[k]=0;
		int i=0;
		if(str[i]=='-')
			flag=true,i++;
		while(str[i])
		{
			res[k]=(res[k]*10LL+str[i]-'0')%MOD[k];
			i++;
		}
		if(flag)
			res[k]=(MOD[k]-res[k])%MOD[k];
	}
}
bool Check(int x,int k)
{
	long long res=0;
	for(int i=n;i>=0;i--)
		res=(res*x%MOD[k]+A[i][k])%MOD[k];
	res=(res+MOD[k])%MOD[k];
	return res==0;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		scanf("%s",str);
		module(A[i]);
	}
	for(int i=1;i<=MOD[0];i++)
		if(Check(i,0))
		{
			for(int j=i;j<=m;j+=MOD[0])
				if(Check(j,1))
					can[j]=true;
		}
	for(int i=1;i<=m;i++)
		if(can[i])
			ans.push_back(i);
	printf("%u\n",ans.size());
	for(int i=0;i<(int)ans.size();i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
