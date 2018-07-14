#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;
int w[MAXN],h[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",w+i,h+i);
	if(w[1]>h[1])
		swap(h[1],w[1]);
	for(int i=2;i<=n;i++)
	{
		int mx=max(w[i],h[i]),mn=min(w[i],h[i]);
		if(mn>h[i-1])
		{
			puts("NO");
			return 0;
		}
		if(mx<=h[i-1])
			h[i]=mx;
		else
			h[i]=mn;
	}
	puts("YES");
	
	return 0;
}
