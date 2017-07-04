#include<iostream> 
#include<cstdio> 
#include<cstring>
using namespace std;
char s[100005];
void tuige(int n,int len)
{
    for(int i=n+1;i<len;i++)
        s[i-1]=s[i];
    s[len-1]=s[len]=0;
}
int main()
{
    gets(s);
    int len=strlen(s);
    for(int i=0,f=0;s[i];i++)
    {
        if(s[i]=='%'&&s[i+1]=='%')f=1;
        if(s[i]=='%')
        {
			if(i==0)
				tuige(i--,len--);
			else if(i==1)
			{tuige(i--,len--);tuige(i--,len--);}
			else
			{
				tuige(i--,len--);
				tuige(i--,len--);
				tuige(i--,len--);
			}
        }
        if(s[i]=='@'&&f)
        {
            s[i]='\n';
            f=0;
        }
        else if(s[i]=='@')
			tuige(i--,len--);
    }
    for(int i=0;s[i];i++)
        printf("%c",s[i]);
    return 0;
}
