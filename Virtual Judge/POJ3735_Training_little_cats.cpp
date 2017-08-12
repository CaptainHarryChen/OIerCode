#include<cstdio>
const int MAXN=105;
struct Matrix
{
	int h,w;
	long long a[MAXN][MAXN];
	Matrix(){h=w=0;}
	Matrix(int h,int w):h(h),w(w)
	{
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
				a[i][j]=0;
	}
	void clear(int _h,int _w)
	{
		h=_h;
		w=_w;
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
				a[i][j]=0;
	}
	Matrix operator * (const Matrix &t)const
	{
		Matrix res(0,0);
		int l=t.h;
		if(l!=this->w)
			return res;
		int h=this->h;
		int w=t.w;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			for(int k=0;k<l;k++)
				if(a[i][k])
					for(int j=0;j<w;j++)
						res.a[i][j]+=a[i][k]*t.a[k][j];
		return res;
	}
	Matrix pow(int b)const
	{
		Matrix res(0,0);
		if(h!=w)
			return res;
		Matrix d=*this;
		res=Matrix(h,w);
		for(int i=0;i<h;i++)
			res.a[i][i]=1;
		while(b)
		{
			if(b&1)
				res=res*d;
			d=d*d;
			b>>=1;
		}
		return res;
	}
};
int op[MAXN][3];
int main()
{
	int n,m,k,x,y;
	char mo[5];
	Matrix matop,temp,pea;
	while(true)
	{
		scanf("%d%d%d",&n,&m,&k);
		if(!n&&!m&&!k)
			break;
		for(int o=1;o<=k;o++)
		{
			scanf("%s%d",mo,op[o]+1);
			if(mo[0]=='g')
				op[o][0]=1;
			if(mo[0]=='e')
				op[o][0]=2;
			if(mo[0]=='s')
			{
				op[o][0]=3;
				scanf("%d",op[o]+2);
			}
		}
		pea.clear(n+1,1);
		pea.a[n][0]=1;
		matop.clear(n+1,n+1);
		for(int i=0;i<=n;i++)
			matop.a[i][i]=1;
		for(int o=k;o>0;o--)
		{
			temp.clear(n+1,n+1);
			for(int i=0;i<=n;i++)
				temp.a[i][i]=1;
			x=op[o][1]-1;
			y=op[o][2]-1;
			if(op[o][0]==1)
			{
				temp.a[x][n]=1;
				matop=matop*temp;
			}
			if(op[o][0]==2)
			{
				temp.a[x][x]=0;
				matop=matop*temp;
			}
			if(op[o][0]==3)
			{
				temp.a[x][x]=0;
				temp.a[x][y]=1;
				temp.a[y][y]=0;
				temp.a[y][x]=1;
				matop=matop*temp;
			}
		}
		pea=matop.pow(m)*pea;
		for(int i=0;i<n-1;i++)
			printf("%lld ",pea.a[i][0]);
		printf("%lld\n",pea.a[n-1][0]);
	}
	return 0;
}
