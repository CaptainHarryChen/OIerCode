#include<cstdio>
template<class T>
void Read(T &x)
{
	char c;
	bool f=0;
	while(c=getchar(),c!=EOF)
	{
		if(c=='-')
			f=1;
		else if(c>='0'&&c<='9')
		{
			x=c-'0';
			while(c=getchar(),c>='0'&&c<='9')
				x=x*10+c-'0';
			if(f)
				x=-x;
			return;
		}
	}
}
int main()
{
	freopen("FastReading_data.in","r",stdin);
	int n=1000;
	while(n--)
	{
		int x;Read(x);
		printf("%d ",x);
	}
	return 0;
}
