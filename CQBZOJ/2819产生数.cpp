#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
queue<string>q;
bool flag[20005];
bool f(string n,int len)
{
    int num=0;
    for(int i=0;i<len;i++)
        num=num*10+n[i]-'0';
    if(flag[num]==0)
    {flag[num]=1;return 1;}
    return 0;
}
int main()
{
    string n;
	cin>>n;
    int k,a[15][2],len=n.size(),cnt=0;
    scanf("%d",&k);
    for(int i=0;i<k;i++)
        scanf("%d%d",&a[i][0],&a[i][1]);
    q.push(n);
    cnt++;
    int num=0;
    for(int i=0;i<len;i++)
        num=num*10+n[i]-'0';
    flag[num]=1;
    while(!q.empty())
    {
        string t=q.front();
        q.pop();
        for(int i=0;i<k;i++)
        {
			string tt=t;
            for(int j=0;j<len;j++)
                if(t[j]-'0'==a[i][0])
                    tt[j]=a[i][1]+'0';
			if(f(tt,len))
				{q.push(tt);cnt++;}
        }
    }
    cout<<cnt<<endl;
    return 0;
}
