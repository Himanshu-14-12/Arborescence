#include<iostream>
#include<vector>
#include<queue>
#include <vector>
#include<stack>
#include<climits>
using namespace std;
#define noEdge 10000000
#define maxxx 999999
int reaching[200]={0};
int x;

// Function to detect the cycle.
void detectCycle(int n, int &Cycle, int &temp, vector<int> ZeroIn);
//Function to track the record of nodes 
int compressionCB(int *compression, int *callBack, int n, int temp, vector<int> FirstZero);
//Function to create arborescence
vector<int> minArbo(int src, int n, vector<int> mat[]);


void DFS(int arr[][200],int t){
    int j;
    reaching[t]=1;
    for(j=0;j<x;j++){
        if(arr[t][j]<maxxx){
            if(reaching[j]==0){
                reaching[j]=1;
                DFS(arr,j);
            }
        }
    }
}

void BFS(int src, int n, vector<int> mat[]){
	int vis[n];
	for (int i = 0; i < n; i++)
	{
		vis[i] = 0;
	}
	queue<int> q;
	vis[src] = true;
	q.push(src);
	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (!vis[i] && mat[t][i] != noEdge)
			{
				vis[i] = 1;
				q.push(i);
			}
		}
	}
	for (int j = 0; j < n; j += 1)
	{
		if (vis[j] == 0)
		{
			for (int k = 0; k < n; k += 1)
			{
				mat[j][k] = noEdge;
				mat[k][j] = noEdge;
			}
		}
	}
}

void detectCycle(int n, int &Cycle, int &flag, vector<int> ZeroIn){
	int visit[n] = {0};
	for (int i = 0; i < n; i++)
	{
		if (visit[i] == 0)
		{
			flag = i;
			while (1)
			{
				if (visit[flag] == 1)
				{
					Cycle = 1;
					break;
				}
				if (ZeroIn[flag] != -1)
				{
					visit[flag] = 1;
					flag = ZeroIn[flag];
				}
				else
					break;
			}
			for (int j = 0; j < n; j++)
			{
				visit[j] = 0;
			}
		}
		if (Cycle)
			break;
	}
}

int compressionCB(int *compression, int *callBack, int n, int temp, vector<int> FirstZero)
{
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		compression[i] = 1;
		callBack[i] = -1;
	}
	int i = temp;
	compression[i] = 0;
	while (1)
	{
		i = FirstZero[i];
		cnt++;
		compression[i] = 0;
		if (i == temp)
			break;
	}

	temp = 1;
	for (int i = 0; i < n; i++)
	{
		if (compression[i] == 1)
		{
			compression[i] = temp;
			callBack[temp - 1] = i;
			temp++;
		}
	}
	return cnt;
}

vector<int> minArbo(int src, int n, vector<int> mat[])
{
	vector<int> redWeight[n];
	vector<int> EdgeZero; 
	int minEdge[n]; 
	int cycle = 0;
	int temp;
	BFS(src, n, mat); 

	for (int i = 0; i < n; i++)
	{
		int temp = INT_MAX;
		for (int j = 0; j < n; j++)
		{
			redWeight[i].push_back(noEdge);
			if (mat[j][i] != noEdge)
			{
				if (mat[j][i] < temp)
					temp = mat[j][i];
			}
		}
		if (temp != INT_MAX)
			minEdge[i] = temp;
		else
			minEdge[i] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		EdgeZero.push_back(-1);
	}
	for (int i = 0; i < n; i += 1)
	{
		for (int j = 0; j < n; j++)
		{
			if (mat[i][j] != noEdge)
				redWeight[i][j] = mat[i][j] - minEdge[j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (redWeight[j][i] == 0)
			{
				EdgeZero[i] = j;
				break;
			}
		}
	}
	detectCycle(n, cycle, temp, EdgeZero);
	if (cycle)
	{
		int callBack[n];
		int compression[n];
		int cnt = compressionCB(compression, callBack, n, temp, EdgeZero);
		int change = n + 1 - cnt;
		int temporary[change];
		vector<int> Matrix[change];
		for (int j = 0; j < change; j++)
		{
			for (int k = 0; k < change; k++)
				Matrix[j].push_back(noEdge);
		}
		for (int j = 0; j < n; j++)
		{
			if (compression[j] == 0)
			{
				for (int k = 0; k < n; k++)
				{
					if (compression[k] != 0)
					{
						if (Matrix[change - 1][compression[k] - 1] == noEdge)
							Matrix[change - 1][compression[k] - 1] = redWeight[j][k];
						else
						{
							if (mat[j][k] != noEdge)
								Matrix[change - 1][compression[k] - 1] = min(Matrix[change - 1][compression[k] - 1], redWeight[j][k]);
						}
					}
				}
			}
			else
			{
				for (int k = 0; k < n; k++)
				{
					if (compression[k] == 0)
					{
						if (Matrix[compression[j] - 1][change - 1] == noEdge)
						{
							if (mat[j][k] != noEdge)
							{
								temporary[compression[j] - 1] = k;
								Matrix[compression[j] - 1][change - 1] = redWeight[j][k];
							}
						}

						else
						{
							if (mat[j][k] != noEdge)
							{
								if (Matrix[compression[j] - 1][change - 1] > redWeight[j][k])
								{
									temporary[compression[j] - 1] = k;
									Matrix[compression[j] - 1][change - 1] = redWeight[j][k];
								}
							}
						}
					}
					else
						Matrix[compression[j] - 1][compression[k] - 1] = redWeight[j][k];
				}
			}
		}
		vector<int> prefin;
		prefin = minArbo(compression[src] - 1, change, Matrix);
		vector<int> fin;
		for (int i = 0; i < n; i++)
		{
			fin.push_back(-1);
		}
		for (int i = 0; i < n; i++)
		{
			if (compression[i] == 0)
				fin.at(i) = EdgeZero.at(i);
			else
			{
				int ele = compression[i] - 1;
				if (prefin.at(ele) == change - 1)
				{
					int tt = INT_MAX;
					int flag = 0;
					for (int j = 0; j < n; j++)
					{
						if (compression[j] == 0)
						{
							if (tt > mat[j][i])
							{
								tt = mat[j][i];
								flag = j + 1;
							}
						}
					}
					if (flag > 0)
						fin.at(i) = flag - 1;
					else
						fin.at(i) = -1;
				}

				else if (prefin.at(ele) == -1)
					fin.at(i) = -1;
				else
					fin.at(i) = callBack[prefin.at(ele)];
			}
		}
		int dobaar = prefin[change - 1];
		if (dobaar != -1)
		{
			int solution = temporary[dobaar];
			fin.at(solution) = callBack[dobaar];
		}

		return fin;
	}
	return EdgeZero;
}

int main()
{
	int t;
	cin >> t;
	for (int tt = 0; tt < t; tt++)
	{
		int N, M, source, u, v, w;
		cin >> N >> M >> source;
		vector<int> matrix[N];
        int validcase=0;
		int invalidCase=0; 
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				matrix[j].push_back(noEdge);
			}
		}
		for (int j = 0; j < M; j++)
		{
			cin >> u >> v >> w;
			if (u != v && v != source)
			{
				if (w < 0)
					invalidCase = 1;
				else if (matrix[u - 1][v - 1] == noEdge)
					matrix[u - 1][v - 1] = w;
				else
					matrix[u - 1][v - 1] = min(matrix[u - 1][v - 1], w);
			}
		}
		if (invalidCase)
			cout << -1 << endl;
		else
		{
			vector<int> v;
			v = minArbo(source - 1,N,matrix);
			int ans[N] = {0};
			int minCostOfArboroscence = 0;
			int temp;
			for (int j = 0; j < N; j++)
			{
				if (v[j] != -1)
					minCostOfArboroscence += matrix[v[j]][j];
			}
			cout << minCostOfArboroscence << " ";
			for (int j = 0; j < N; j++)
			{
				int temp = j;
				if (v[temp] == -1)
					ans[j] = -1;
				else
				{
					while (1)
					{
						if (temp != source - 1)
						{
							ans[j] += matrix[v[temp]][temp];
							temp = v[temp];
						}
						else
							break;
					}
				}
			}
			for (int j = 0; j < N; j++)
			{
				if (j + 1 == source)
					cout << 0 << " ";
				else
					cout << ans[j] << " ";
			}
			cout << "# ";
			for (int j = 0; j < N; j++)
			{
				if (j + 1 == source)
					cout << 0 << " ";
				else if (v[j] == -1)
					cout << -1 << " ";
				else
					cout << v[j] + 1 << " ";
			}
			cout << endl;
		}
	}
    /*
    double time_taken; 
        time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
        time_taken = (time_taken + (end.tv_usec -  start.tv_usec)) * 1e-6; 

        cout << "Time taken by program is : " << fixed << time_taken << setprecision(6); 
        cout << " sec" << endl;
        */
    return 0;
}