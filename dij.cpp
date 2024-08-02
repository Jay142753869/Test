#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#define R register
using namespace std;
inline int read(){
	R int x=0,f=0;char ch=getchar();
	while(ch>'9'||ch<'0')f^=ch=='-',ch=getchar();
	while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
struct edge{
	int to,dis,nt;
}e[500010];
int head[100010],dis[100010],cnt;
bool vis[100010];
inline void add(int u,int v,int w){
	e[++cnt].dis=w,e[cnt].to=v,e[cnt].nt=head[u];
	head[u]=cnt;
}
struct node{
	int dis,pos;
	inline bool operator<(const node &s)const {
		return s.dis<dis;
	}
};
priority_queue<node> q;
inline void dij(int s){
	dis[s]=0;
	q.push((node){0,s});
	while(!q.empty()){
		node tmp=q.top();
		q.pop();
		int x=tmp.pos,d=tmp.dis;
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=e[i].nt){
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].dis){
				dis[y]=dis[x]+e[i].dis;
				if(!vis[y])q.push((node){dis[y],y});
			}
		}
	}
}
int n,m,s;
int main(){
	n=read(),m=read(),s=read();
	for(int i=1;i<=n;i++)dis[i]=0x7fffffff;
	for(int i=0;i<m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	dij(s);
	for(int i=1;i<=n;i++)printf("%d ",dis[i]);
	puts("");
	return 0;
}
