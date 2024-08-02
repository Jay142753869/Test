#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
#define maxn 2010
#define maxm 6010
using namespace std;
int t,n,m;
int dis[maxn],head[maxn],cnt[maxn],tot;
bool vis[maxn]; 
struct node{
	int to,w,nt;
}edge[maxm];
inline int read(){
	int a=0,b=0;
	char ch=getchar();
	while(!isdigit(ch))b^=ch=='-',ch=getchar();
	while(isdigit(ch))a=a*10+(ch-'0'),ch=getchar();
	return b?-a:a;
}
inline void add(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].w=w;
	edge[tot].nt=head[u];
	head[u]=tot;
}
inline void pre(){
	for(int i=1;i<=maxm;i++)edge[i].nt=0;
	for(int i=1;i<=maxn;i++)head[i]=0;
	tot=0;
}
inline void Init(){
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
}
inline bool spfa(int t){
	Init();
	queue<int> q;
	q.push(t);
	dis[t]=0,cnt[t]=0,vis[t]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=edge[i].nt){
			int v=edge[i].to,w=edge[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>=n)return 1;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return 0;
}
int main(){
	t=read();
	while(t--){
		pre();
		n=read(),m=read();
		for(int i=1;i<=m;i++){
			int u=read(),v=read(),w=read();
			if(w>=0){
				add(u,v,w);
				add(v,u,w);
			}
			else add(u,v,w);
		}
		spfa(1)?puts("YES"):puts("NO");
	}
	return 0;
}
