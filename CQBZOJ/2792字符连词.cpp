#include<iostream> 
#include<cstdio> 
#include<cstring>
using namespace std;
char s[10005][1005],m[10005],mm;
int main()
{
	int n;
	for(n=0;gets(s[n]);n++);
	for(int i=0;i<n;i++)
		for(int j=0;s[i][j];j++)
			if(((s[i][j]>=0&&s[i][j]<=9)||(s[i][j]>='A'&&s[i][j]<='Z')||(s[i][j]>='a'&&s[i][j]<='z'))&&s[i][j]>m[i])
				m[i]=s[i][j];
	puts(m);
	for(int i=0;i<n;i++)
		if(m[i]>mm)
			mm=m[i];
	printf("%c\n",mm);
	return 0;
}
