#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
#define maxn 100010
#define ll long long
using namespace std;
int n,m,mod;
ll a[maxn];
struct node{ll ans,add,mul;}s[maxn<<2];
inline ll read(){
	int a=0,b=0;
	char ch=getchar();
	while(!isdigit(ch))b^=ch=='-',ch=getchar();
	while(isdigit(ch))a=a*10+(ch-'0'),ch=getchar();
	return b?-a:a;
}
inline void lazy(int fa,int l,int r,ll n,ll m){
	s[fa].add=(s[fa].add*m+n)%mod;
	s[fa].mul=(s[fa].mul*m)%mod;
	s[fa].ans=(s[fa].ans*m+(r-l+1)*n)%mod;
}
inline void push_up(int fa){s[fa].ans=(s[fa<<1].ans+s[fa<<1|1].ans)%mod;}
inline void push_down(int fa,int l,int r){
	int mid=(l+r)>>1;
	lazy(fa<<1,l,mid,s[fa].add,s[fa].mul);
	lazy(fa<<1|1,mid+1,r,s[fa].add,s[fa].mul);
	s[fa].add=0;
	s[fa].mul=1;
}
inline void build(int fa,int l,int r){
	s[fa].add=0;
	s[fa].mul=1; 
	if(l==r){
		s[fa].ans=a[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(fa<<1,l,mid);
	build(fa<<1|1,mid+1,r);
	push_up(fa); 
}
inline void mul(int fa,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr){
		s[fa].ans=(s[fa].ans*k)%mod;
		s[fa].add=(s[fa].add*k)%mod;
		s[fa].mul=(s[fa].mul*k)%mod;
		return;
	}
	int mid=(l+r)>>1;
	push_down(fa,l,r);
	if(ql<=mid)mul(fa<<1,l,mid,ql,qr,k);
	if(qr>mid)mul(fa<<1|1,mid+1,r,ql,qr,k);
	push_up(fa);
}
inline void add(int fa,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr){
		s[fa].ans=(s[fa].ans+(r-l+1)*k)%mod;
		s[fa].add=(s[fa].add+k)%mod;
		return;
	}
	int mid=(l+r)>>1;
	push_down(fa,l,r);
	if(ql<=mid)add(fa<<1,l,mid,ql,qr,k);
	if(qr>mid)add(fa<<1|1,mid+1,r,ql,qr,k);
	push_up(fa);
}
inline ll query(int fa,int l,int r,int ql,int qr){
	ll res=0;
	if(ql<=l&&r<=qr)return s[fa].ans;
	int mid=(l+r)>>1;
	push_down(fa,l,r);
	if(ql<=mid)res=(res+query(fa<<1,l,mid,ql,qr))%mod;
	if(qr>mid)res=(res+query(fa<<1|1,mid+1,r,ql,qr))%mod;
	return res;
}
int main(){
	n=read(),m=read(),mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int j=read();
		if(j==1){
			int l=read(),r=read(),k=read();
			add(1,1,n,l,r,k);
		}
		if(j==2){
			int l=read(),r=read(),k=read();
			add(1,1,n,l,r,k);
		}
		if(j==3){
			int l=read(),r=read();
			printf("%lld\n",query(1,1,n,l,r));
		}
	}
	return 0;
}
