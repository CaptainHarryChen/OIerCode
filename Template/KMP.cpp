#include<cstdio>
#include<cstring>
const int MAXN=1000005;

char A[MAXN],B[MAXN];
int fail[MAXN];

int main()
{
	freopen("KMP_data.in","r",stdin);
	scanf("%s%s",A,B);
	int len1=strlen(A),len2=strlen(B);
	memset(fail,-1,sizeof fail);
	for(int i=1;i<len2;i++)
	{
		int j=fail[i-1];
		while(j!=-1&&B[j+1]!=B[i])
			j=fail[j];
		fail[i]=(B[j+1]!=B[i]?-1:j+1);
	}
	for(int i=0,j=-1;i<=len1;i++)
	{
		if(j>=len2-1)
		{
			printf("yes\n%d\n",i-j-1);
			return 0;
		}
		while(j!=-1&&A[i]!=B[j+1])
			j=fail[j];
		if(A[i]==B[j+1])
			j++;
	}
	printf("no\n");
	
	return 0;
}
