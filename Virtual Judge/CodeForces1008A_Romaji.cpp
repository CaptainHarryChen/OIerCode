#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;

char str[MAXN];

int main()
{
	scanf("%s",str);
	int n=strlen(str);
	for(int i=0;i<n;i++)
		if(!(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='n'))
			if(!(str[i+1]=='a'||str[i+1]=='e'||str[i+1]=='i'||str[i+1]=='o'||str[i+1]=='u'))
			{
				puts("NO");
				return 0;
			}
	puts("YES");
	return 0;
}
