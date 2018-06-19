#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=105;

map<char,string> mA;
map<string,char> mB;

void Init()
{
	mA['A']=".-"  ;mB[".-"  ]='A';
	mA['B']="-...";mB["-..."]='B';
	mA['C']="-.-.";mB["-.-."]='C';
	mA['D']="-.." ;mB["-.." ]='D';
	mA['E']="."   ;mB["."   ]='E';
	mA['F']="..-.";mB["..-."]='F';
	mA['G']="--." ;mB["--." ]='G';
	mA['H']="....";mB["...."]='H';
	mA['I']=".."  ;mB[".."  ]='I';
	mA['J']=".---";mB[".---"]='J';
	mA['K']="-.-" ;mB["-.-" ]='K';
	mA['L']=".-..";mB[".-.."]='L';
	mA['M']="--"  ;mB["--"  ]='M';
	mA['N']="-."  ;mB["-."  ]='N';
	mA['O']="---" ;mB["---" ]='O';
	mA['P']=".--.";mB[".--."]='P';
	mA['Q']="--.-";mB["--.-"]='Q';
	mA['R']=".-." ;mB[".-." ]='R';
	mA['S']="..." ;mB["..." ]='S';
	mA['T']="-"   ;mB["-"   ]='T';
	mA['U']="..-" ;mB["..-" ]='U';
	mA['V']="...-";mB["...-"]='V';
	mA['W']=".--" ;mB[".--" ]='W';
	mA['X']="-..-";mB["-..-"]='X';
	mA['Y']="-.--";mB["-.--"]='Y';
	mA['Z']="--..";mB["--.."]='Z';
	mA['_']="..--";mB["..--"]='_';
	mA[',']=".-.-";mB[".-.-"]=',';
	mA['.']="---.";mB["---."]='.';
	mA['?']="----";mB["----"]='?';
}

string str,code,ans;
vector<int> fig;

int main()
{
	Init();
	int n;
	cin>>n;
	for(int cas=1;cas<=n;cas++)
	{
		str.clear();
		code.clear();
		ans.clear();
		fig.clear();
		cin>>str;
		for(int i=0;i<(int)str.length();i++)
		{
			code+=mA[str[i]];
			fig.push_back(mA[str[i]].length());
		}
		reverse(fig.begin(),fig.end());
		
		for(int i=0,j=0;i<(int)fig.size();i++)
			ans+=mB[code.substr(j,fig[i])],j+=fig[i];
		cout<<cas<<": "<<ans<<endl;
	}
	
	return 0;
}
