#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Balance
{
    static const int MAXN=53,MAXNODE=2505;
    const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

    int N;
    int id[MAXN][MAXN],idc;

    int fa[MAXNODE],siz[MAXNODE];

    int Mark(const vector<string> &grid,int x,int y,int c)
    {
        int res=-1,tmp;
        id[x][y]=c;
        for(int d=0;d<4;d++)
        {
            int tx=x+dir[d][0],ty=y+dir[d][1];
            if(tx<0||ty<0||tx>=N||ty>=N)
            {
                res=0;
                continue;
            }
            if(grid[x][y]!=grid[tx][ty])
            {
                if(id[tx][ty]!=-1)
                    res=id[tx][ty];
                continue;
            }
            if(id[tx][ty]==-1)
            {
                tmp=Mark(grid,tx,ty,c);
                if(tmp!=-1)
                    res=tmp;
            }
        }
        return res;
    }

    void MakeTree(const vector<string> &grid,vector<int> &res)
    {
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                id[i][j]=-1;
        idc=0;
        for(int i=0;i<N;i++)
        {
            if(id[i][0]==-1&&grid[i][0]=='#')
                Mark(grid,i,0,idc);
            if(id[i][N-1]==-1&&grid[i][N-1]=='#')
                Mark(grid,i,N-1,idc);
        }
        for(int j=0;j<N;j++)
        {
            if(id[0][j]==-1&&grid[0][j]=='#')
                Mark(grid,0,j,idc);
            if(id[N-1][j]==-1&&grid[N-1][j]=='#')
                Mark(grid,N-1,j,idc);
        }
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                if(id[i][j]==-1)
                {
                    idc++;
                    fa[idc]=Mark(grid,i,j,idc);
                }
        for(int i=0;i<=idc;i++)
            siz[i]=0;
        for(int i=idc;i>=0;i--)
        {
            siz[i]++;
            if(i!=0)
                siz[fa[i]]+=siz[i];
        }
        sort(siz,siz+idc+1);
        for(int i=0;i<=idc;i++)
            res.push_back(siz[i]);
    }

public:
    string canTransform(const vector<string> &initial,const vector<string> &target)
    {
        N=initial.size();
        vector<int> A,B;
        MakeTree(initial,A);
        MakeTree(target,B);
        if(A!=B)
            return "Impossible";
        return "Possible";
    }
};