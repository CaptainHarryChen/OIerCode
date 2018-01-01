#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	int cnt[3]={0},n,a;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a),cnt[a]++;
	printf("%d\n",min(cnt[2],cnt[1])+(cnt[1]-min(cnt[2],cnt[1]))/3);
	return 0;
}
