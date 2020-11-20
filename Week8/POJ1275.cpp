#include<algorithm>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

// SPFA algorithm implementation
// m: # of vertices
int SPFA(int m, const vector<vector<int>>& adjList)
{
  if (m == 0)
    return INT_MAX;

  vector<vector<vector<int>>> edges(m, vector<vector<int>>());
  for (auto& list: adjList)
    edges[list[0]].push_back(vector<int>(list.begin() + 1, list.end()));

  vector<int> dist(m, INT_MAX);
  vector<bool> inq(m, false);
  vector<int> count(m, 0);
  dist[0] = 0;
  queue<int> q;
  q.push(0);
  inq[0] = true;
  while(!q.empty())
  {
    int u = q.front();
    q.pop();
    inq[u] = false;
    if (++count[u] > m - 1)
    {
      // Negative cycle detected
      return INT_MAX;
    }
    for (const auto& edge: edges[u])
    {
      int v = edge[0], w = edge[1];
      int tmp = dist[u] + w;
      if (tmp < dist[v])
      {
        dist[v] = tmp;
        if (!inq[v])
        {
          q.push(v);
          inq[v] = true;
        }
      }
    }
  }

  return dist[m - 1];
}

void buildAdjList(int T, const vector<int>& t, const vector<int>& R, vector<vector<int>>& adjList)
{
  for (int i = 1; i < 25; ++i)
  {
    adjList.push_back({i - 1, i, 0});
    adjList.push_back({i, i - 1, t[i]});
  }
  for (int i = 17; i <= 24; ++i)
  {
    int j = (i + 8) % 24;
    adjList.push_back({i, j, -R[j] + T});
  }
  for (int i = 1; i < 17; ++i)
  {
    int j = i + 8;
    adjList.push_back({i, j, -R[j]});
  }
  adjList.push_back({0, 24, -T});
  /*
  for (int i = 7; i < 24; ++i)
    adjList.push_back({i + 1, i - 7, -R[i]});
  for (int i = 0; i < 7; ++i)
    adjList.push_back({i + 1, i + 17, T - R[i]});
  for (int i = 0; i < 24; ++i)
    adjList.push_back({i + 1, i, 0});
  for (int i = 0; i < 24; ++i)
    adjList.push_back({i, i + 1, t[i]});
  adjList.push_back({24, 0, -T});
  */
  //adjList.push_back({0, 24, T});
}

void invoker()
{
  // Read input
  int N, tmp;
  vector<int> R(25, 0);
  for (int i = 1; i < 25; ++i)
  {
    cin >> tmp;
    R[i] = tmp;
  }
  cin >> N;

  vector<int> t(25, 0);
  for (int i = 0; i < N; ++i)
  {
    cin >> tmp;
    ++t[tmp + 1];
  }

  int l = 1, h = N, res;
  while(l <= h)
  {
    int m = (h - l) / 2 + l;
    vector<vector<int>> adjList;
    buildAdjList(m, t, R, adjList);

    res = SPFA(25, adjList);
    if (res == -m)
    {
      if (l == h)
      {
        cout << m << endl;
        return;
      }
      else
        h = m;
    }
    else
      l = m + 1;
  }

/*
  for (int T = 1; T <= N; ++T)
  {
    vector<vector<int>> adjList;
    buildAdjList(T, t, R, adjList);
    
    int res = SPFA(25, adjList);
    if(res == -T)
    {
      cout << T << endl;
      return;
    }
  }
*/
  cout << "No Solution" << endl;
  return;
}

int main()
{
  /*
  vector<vector<int>> adjList0{{0, 1, 1}, {1, 2, 7}, {1, 3, -2}, {0, 2, 8}, {0, 3, 9}, {2, 3, 3}, {1, 4, 3}, {3, 4, -3}};
  cout << SPFA(5, adjList0) << endl;
  vector<vector<int>> adjList1{{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 4}, {3, 1, 1}, {4, 3, 3}};
  cout << SPFA(5, adjList1) << endl;
  vector<vector<int>> adjList2{{0, 1, 1}, {1, 2, -3}, {2, 0, -1}, {2, 3, 3}};
  cout << SPFA(4, adjList2) << endl;    // Negative cycle test case
*/
  
  int nCases;
  cin >> nCases;
  for (int i = 0; i < nCases; ++i)
    invoker();

  return 0;
}
