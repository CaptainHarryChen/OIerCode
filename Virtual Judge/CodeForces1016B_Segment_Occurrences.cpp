#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n,m,q;
char A[MAXN],B[MAXN];
vector<int> occ;

int main()
{
	scanf("%d%d%d%s%s",&n,&m,&q,A,B);
	int lenb=strlen(B);
	char *it=A,*tmp;
	tmp=strstr(it,B);
	while(tmp!=NULL)
	{
		occ.push_back(tmp-A);
		it=tmp+1;
		tmp=strstr(it,B);
	}
	for(int i=1;i<=q;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		a--;b--;
		b-=lenb-1;
		if(b<a)
			puts("0");
		else
			printf("%d\n",upper_bound(occ.begin(),occ.end(),b)-lower_bound(occ.begin(),occ.end(),a));
	}
	
	return 0;
}
