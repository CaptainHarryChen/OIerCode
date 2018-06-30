#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2000005;
typedef pair<int,int> Cow;

Cow c[MAXN];
bool cmp(const Cow &a,const Cow &b)
{return 1.0*a.first/a.second<1.0*b.first/b.second;}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&c[i].first,&c[i].second);
	sort(c+1,c+n+1,cmp);
	int S=0;
	for(int i=1;i<=n;i++)
		S+=c[i].second;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		S-=c[i].second;
		ans+=2LL*c[i].first*S;
	}
	printf("%lld\n",ans);
	return 0;
}

/*
(S+Dj)*2*Ti+S*2*Tj<(S+Di)*2*Tj+S*2*Ti
S*2*(Ti+Tj)+Dj*Ti*2<S*2*(Ti+Tj)+Di*Tj*2
Dj*Ti<Di*Tj
Ti/Di<Tj/Dj
*/
