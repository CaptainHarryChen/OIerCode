#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=53;

vector<int> cX,cY,vX,vY;
double dis(int x1,int y1,int x2,int y2)
{return sqrt(pow(1.0*x1-x2,2.0)+pow(1.0*y1-y2,2.0));}
int cmpid;
bool cmp(int a,int b)
{
	return dis(vX[cmpid],vY[cmpid],vX[a],vY[a])<dis(vX[cmpid],vY[cmpid],vX[b],vY[b]);
}

class KingdomXCitiesandVillages
{
	int toCity[MAXN];
	vector<int> toVil[MAXN];
	
public:
	double determineLength(vector<int> &cityX,vector<int> &cityY,vector<int> &villageX,vector<int> &villageY)
	{
		cX=cityX;cY=cityY;vX=villageX;vY=villageY;
		int m=cX.size(),n=vX.size();
		for(int i=0;i<n;i++)
		{
			double mn=1e100,d;
			for(int j=0;j<m;j++)
			{
				d=dis(vX[i],vY[i],cX[j],cY[j]);
				if(mn>d)
					mn=d,toCity[i]=j;
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
				if(i!=j&&dis(vX[i],vY[i],vX[j],vY[j])<dis(vX[i],vY[i],cX[toCity[i]],cY[toCity[i]]))
					toVil[i].push_back(j);
			cmpid=i;
			sort(toVil[i].begin(),toVil[i].end(),cmp);
		}
		
		double ans=0;
		for(int i=0;i<n;i++)
		{
			double P=1.0,p;
			for(int j=0;j<(int)toVil[i].size();j++)
			{
				p=1.0/(j+1.0)/(j+2.0);
				P-=p;
				ans+=p*dis(vX[i],vY[i],vX[toVil[i][j]],vY[toVil[i][j]]);
			}
			ans+=P*dis(vX[i],vY[i],cX[toCity[i]],cY[toCity[i]]);
		}
		
		return ans;
	}
};
