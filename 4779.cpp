#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#define FILE(a) freopen(a".in","r",stdin),freopen(a".ans","w",stdout)
#define maxn 100010
#define maxm 500010
using namespace std;
int n,m,s,dis[maxn],head[maxn],tot;
bool vis[maxn];
inline int read(){
	int a=0,b=0;
	char ch=getchar();
	while(!isdigit(ch))b^=ch=='-',ch=getchar();
	while(isdigit(ch))a=a*10+(ch-'0'),ch=getchar();
	return b?-a:a;
}
struct node{
	int to,w,nt;
}edge[maxm];
struct p{
	int dis,pos;
	inline bool operator<(const p &s)const {
		return s.dis<dis;
	}
};
inline void add(int u,int v,int w){
	edge[++tot].to=v;
	edge[tot].w=w;
	edge[tot].nt=head[u];
	head[u]=tot;
}
inline void dij(int s){
	dis[s]=0;
	priority_queue<p> q;
	p tmp;
	tmp.dis=0,tmp.pos=s;
	q.push(tmp);
	while(!q.empty()){
		p a=q.top();
		q.pop();
		int x=a.pos;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=edge[i].nt){
			int v=edge[i].to,w=edge[i].w;
			if(dis[v]>dis[x]+w){
				dis[v]=dis[x]+w;
				p tmp;
				tmp.dis=dis[v],tmp.pos=v;
				if(!vis[v])q.push(tmp);
			}
		}
	}
}
int main(){
	n=read(),m=read(),s=read();
	memset(dis,0x3f3f3f3f,sizeof(dis));
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	dij(s);
	for(int i=1;i<=n;i++)printf("%d ",dis[i]);
	return 0;
}
