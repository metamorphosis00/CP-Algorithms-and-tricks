#include <bits/stdc++.h>
using namespace std;
const int inf=2012345678;
long long dist[10][10];
char b[2010101];
int main(){
	scanf("%s",b);
	int n=strlen(b);
	for(int x=0;x<10;x++)for(int y=0;y<10;y++){
		for(int i=0;i<10;i++)for(int j=0;j<10;j++)dist[i][j]=inf;
		for(int i=0;i<10;i++)dist[i][(i+x)%10]=dist[i][(i+y)%10]=1;
		for(int i=0;i<10;i++)for(int j=0;j<10;j++)for(int k=0;k<10;k++){
			dist[j][k]=min(dist[j][k],dist[j][i]+dist[i][k]);
		}
		//for(int i=0;i<10;i++)for(int j=0;j<10;j++)printf("%d %d %d %d %d\n",x,y,i,j,dist[i][j]);
		bool bad=false;
		long long ans=0;
		for(int i=0;i<n-1;i++){
			int s=b[i]-'0',e=b[i+1]-'0';
			if(dist[s][e]==inf){
				bad=true;break;
			}
			ans+=dist[s][e]-1;
		}
		printf("%lld ",bad?-1LL:ans);
		if(y==9)puts("");
	}
}
