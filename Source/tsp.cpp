#include <bits/stdc++.h>
using namespace std;
void printing(vector<int> &route)
{
	for(int i=0;i<route.size();i++)
		cout<<route[i]<<" ";
	cout<<endl;
}

float cost(vector<int> &route,vector<pair<float,float> > &points,vector<vector<float> > &dist)
{
	float ans=0;
	int n=route.size();
	for(int i=0;i<n-1;i++)
		ans+=dist[route[i]][route[i+1]];
	ans+=dist[route[n-1]][route[0]];
	return ans;
}

vector<int> opt2(vector<int> &route,int i,int j)
{
	vector<int> temp;
	for(int k=0;k<i;k++)
		temp.push_back(route[k]);
	for(int k=j;k>=i;k--)
		temp.push_back(route[k]);
	for(int k=j+1;k<route.size();k++)
		temp.push_back(route[k]);
	return temp;
}

int main()
{
	ios_base::sync_with_stdio(false);
        cin.tie(NULL);
	string s;
	cin>>s;
	int n;
	cin>>n;
	vector<pair<float,float> > points;
	int i,j;
	for(i=0;i<n;i++)
	{
		pair<float,float> temp;
		cin>>temp.first;
		cin>>temp.second;
		points.push_back(temp);
	}
	vector<vector<float> > dist;
	for(i=0;i<n;i++)
	{
		vector<float> tem;
		float qx;
		for(j=0;j<n;j++)
		{
			cin>>qx;
			tem.push_back(qx);
		}
		dist.push_back(tem);
	}
	vector<int> route;
	if(n>=500)
	{
		bool visited[n];
		for(i=0;i<n;i++)
			visited[i]=false;
		visited[0]=true;
		int count=0;
		i=0;
		int minj=i;
		while(count<n-1)
		{
			float t1,mint=INT_MAX;
			minj=i;
			route.push_back(minj);
			for(j=0;j<n;j++)
			{
				if(!visited[j] & j!=i)
				{
					t1=dist[i][j];
					if(t1<mint)
					{
						mint=t1;
						minj=j;
					}
				}
			}
			visited[minj]=true;
			i=minj;
			count++;
		}
		route.push_back(minj);
		printing(route);
		float improv=1;
		while(improv)
		{
			improv=0;
			bool flag=false;
			int initial=cost(route,points,dist);
			vector<int> temp;
			for(i=1;i<n-1;i++)
			{
				if(flag)
					break;
				for(j=i+1;j<n;j++)
				{
					if(flag)
						break;
					temp=opt2(route,i,j);
					int now=cost(temp,points,dist);
					if(now<initial)
					{
						route=temp;
						improv=initial-now;
						flag=true;
						printing(route);
						break;
					}
				}
			}
		}
	}
	else
	{
		for(i=0;i<n;i++)
			route.push_back(i);
		printing(route);
	}
	float T=100000000;
	vector<int> best_route=route;
	float best_cost=cost(best_route,points,dist);
	while(T>0.0)
	{
		float curr_cost=cost(route,points,dist);
		int p1=rand()%n;
		int p2=-1;
		while(p2<0 || p2==p1)
			p2=rand()%n;
		vector<int> new_route=opt2(route,min(p1,p2),max(p1,p2));
		double prob=1.0;
		float new_cost=cost(new_route,points,dist);
		double qw=(1.0*(new_cost-curr_cost))/(T*1.0);
		float tt=exp(qw);
		prob=prob/(1.0+tt);
		float r = ((double) rand() / (RAND_MAX));
		if(r<=prob)
		{
			route=new_route;
			if(new_cost<best_cost)
			{
				best_route=route;
				best_cost=new_cost;
				printing(best_route);
			}
			T=T*0.9999;
		}		
	}
    return 0;
}