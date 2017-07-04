#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 300300
#define MAXM 202
#define INF 2147483647
char a[MAXN],b[MAXM];
long long ans;
int f[MAXM];
int main()
{
	scanf("%s%s",a,b);
	int lena=strlen(a),lenb=strlen(b);
	for(int i=0;i<lena;i++)
	{
		f[0]=i+1;
		for(int j=lenb-1;j>=0;j--)
			if(a[i]==b[j])
				f[j+1]=f[j];
		ans+=f[lenb];
	}
	printf("%I64d\n",ans);
	return 0;
}
