#include<cstdio>
#include<cstring>

int main()
{
	char bal[3][3][15];
	int T;
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				scanf("%s",bal[i][j]);
		for(int f=0;f<12;f++)
		{
			bool flag=true;
			for(int i=0;i<3&&flag;i++)
			{
				int w=0;
				for(int j=0;bal[i][0][j];j++)
					w+=(bal[i][0][j]!=f+'A');
				for(int j=0;bal[i][1][j];j++)
					w-=(bal[i][1][j]!=f+'A');
				if(strcmp(bal[i][2],"up")==0)
					flag=(w>0);
				if(strcmp(bal[i][2],"down")==0)
					flag=(w<0);
				if(strcmp(bal[i][2],"even")==0)
					flag=(w==0);
			}
			if(flag)
				printf("%c is the counterfeit coin and it is light.\n",f+'A');
		}
		for(int f=0;f<12;f++)
		{
			bool flag=true;
			for(int i=0;i<3&&flag;i++)
			{
				int w=0;
				for(int j=0;bal[i][0][j];j++)
					w+=(bal[i][0][j]==f+'A');
				for(int j=0;bal[i][1][j];j++)
					w-=(bal[i][1][j]==f+'A');
				if(strcmp(bal[i][2],"up")==0)
					flag=(w>0);
				if(strcmp(bal[i][2],"down")==0)
					flag=(w<0);
				if(strcmp(bal[i][2],"even")==0)
					flag=(w==0);
			}
			if(flag)
				printf("%c is the counterfeit coin and it is heavy.\n",f+'A');
		}
	}
	return 0;
}
