#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005;

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

struct data
{
    int j;
    int l,r;
    data(){}
    data(int j,int l,int r):j(j),l(l),r(r){}
};

int n,A[MAXN],ans[MAXN];

int hd,tl;
data Q[MAXN];

//(j<i)   p>=a[j]-a[i]+sqrt(i-j)
double val(int i,int j)
{return A[j]+sqrt(i-j);}

void DP()
{
    hd=tl=1;
    Q[1]=data(1,2,n);
    for(int i=2;i<=n;i++)
    {
        while(hd<=tl&&Q[hd].r<i)
            hd++;
        Q[hd].l=i;
        ans[i]=max(ans[i],(int)ceil(val(i,Q[hd].j)-A[i]));
        while(hd<=tl&&val(Q[tl].l,Q[tl].j)<val(Q[tl].l,i))
            tl--;
        if(hd>tl)
            Q[++tl]=data(i,i,n);
        else
        {
            int L=Q[tl].l,R=Q[tl].r,res=Q[tl].r+1;
            while(L<=R)
            {
                int mid=(L+R)/2;
                if(val(mid,Q[tl].j)<val(mid,i))
                    res=mid,R=mid-1;
                else
                    L=mid+1;
            }
            if(res!=Q[tl].l)
                Q[tl].r=res-1;
            else
                tl--;
            if(res<=n)
                Q[++tl]=data(i,res,n);
        }
    }
}

int main()
{
    Read(n);
    for(int i=1;i<=n;i++)
        Read(A[i]);

    DP();
    reverse(A+1,A+n+1);
    reverse(ans+1,ans+n+1);
    DP();
    reverse(ans+1,ans+n+1);

    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);

    return 0;
}
