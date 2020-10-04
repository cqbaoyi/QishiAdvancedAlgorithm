#include<cfloat>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>

#include "hashheap.hpp"

using namespace std;

void updateHeap(hashheap& heap, unordered_map<char, double>& f, char w)
{
  // When the vertex w is in the heap, remove it first
  if (heap.isIn(w))
    heap.remove(w);
  heap.insert(make_pair(w, f[w]));
}

// Implementation of A* search algorithm with a hashheap.
void Astar(int m, int n, unordered_map<char, vector<pair<char, double>>>& adjList, unordered_map<char, double>& h, char dest)
{
  if (m <= 1)
    return;

  unordered_set<char> X = {'A'};
  unordered_map<char, double> g, f;
  g['A'] = 0;
  for (int i = 1; i < m; ++i)
    g['A' + i] = DBL_MAX;
  f['A'] = g['A'] + h['A'];
 
  auto heap = hashheap({{'A', f['A']}});
  // Main loop
  while(!heap.empty())
  {
    if (heap.top().first == dest)
    {
      cout << g[dest] << endl;
      return;
    }

    auto [v, key_v] = heap.extractMin();
    X.insert(v);

    for (auto edge: adjList[v])
    {
      char w = edge.first;
      if (X.find(w) != X.end())
        continue;

      double g_tmp = g[v] + edge.second;
      if (g_tmp < g[w])
      {
        g[w] = g_tmp;
        f[w] = g[w] + h[w];
        updateHeap(heap, f, w);
      }
    }
  }

  cout << "Fail to compute" << endl;
}

int main()
{
  // # of nodes
  int m = 10;
  // # of edges
  int n = 13;

  unordered_map<char, vector<pair<char, double>>> adjList;
  adjList['A'] = vector<pair<char, double>>{make_pair('B', 6), make_pair('F', 3)};
  adjList['B'] = vector<pair<char, double>>{make_pair('A', 6), make_pair('C', 3), make_pair('D', 2)};
  adjList['C'] = vector<pair<char, double>>{make_pair('B', 3), make_pair('D', 1), make_pair('E', 5)};
  adjList['D'] = vector<pair<char, double>>{make_pair('B', 2), make_pair('C', 1), make_pair('E', 8)};
  adjList['E'] = vector<pair<char, double>>{make_pair('C', 5), make_pair('D', 8), make_pair('I', 5), make_pair('J', 5)};
  adjList['F'] = vector<pair<char, double>>{make_pair('A', 3), make_pair('G', 1), make_pair('H', 7)};
  adjList['G'] = vector<pair<char, double>>{make_pair('F', 1), make_pair('I', 3)};
  adjList['H'] = vector<pair<char, double>>{make_pair('F', 7), make_pair('I', 2)};
  adjList['I'] = vector<pair<char, double>>{make_pair('E', 5), make_pair('G', 3), make_pair('H', 2), make_pair('J', 3)};

  unordered_map<char, double> h;
  h['A'] = 10;
  h['B'] = 6;
  h['C'] = 5;
  h['D'] = 7;
  h['E'] = 3;
  h['F'] = 6;
  h['G'] = 5;
  h['H'] = 3;
  h['I'] = 1;
  h['J'] = 0;

  Astar(m, n, adjList, h, 'J');

  return 0;

}
