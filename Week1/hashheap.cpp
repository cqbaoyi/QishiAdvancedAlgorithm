//#include<initializer_list>
//#include<vector>
//#include<unordered_map>
//#include<stdexcept>

#include "hashheap.hpp"

// Implementation of a min-hashheap.
// It supports the deletion of any given value on top of a traditional heap
// by maintatining O(log N) time complexity.
hashheap::hashheap()
{
}

hashheap::hashheap(initializer_list<pair<char, double>> l)
{
  for (auto element: l)
    insert(element);
}

bool hashheap::empty()
{
  return data.empty();
}

pair<char, double> hashheap::top()
{
  return data[0];
}

pair<char, double> hashheap::extractMin()
{
  pair<char, double> res = data.front();

  char c = res.first;
  remove(c);

  return res;
}

void hashheap::insert(pair<char, double> element)
{
  data.push_back(element);
  indexTable[element.first] = data.size() - 1;

  int idx = indexTable[element.first];
  while(idx > 0)
  {
    int idx_p = parent(idx);
    if (data[idx].second < data[idx_p].second)
    {
      int tmp = indexTable[data[idx].first];
      indexTable[data[idx].first] = indexTable[data[idx_p].first];
      indexTable[data[idx_p].first] = tmp;

      swap(data[idx], data[idx_p]);
      idx = idx_p;
    }
    else
      break;
  }
}

bool hashheap::isIn(char c)
{
  return indexTable.find(c) != indexTable.end();
}

// Remove an arbitrary element from the heap
void hashheap::remove(char c)
{
  if (!isIn(c))
    throw runtime_error("No such character in the heap to remove."); 

  int idx = indexTable[c];

  // Change the index of the last element
  indexTable[data.back().first] = idx;
  // Remove one key from indexTable
  indexTable.erase(c);

  // Swap the data
  swap(data[idx], data.back());

  data.pop_back();

  if (!data.empty())
    heapify(idx);
}

void hashheap::print()
{
  for (int i = 0; i < data.size(); ++i)
  {
    cout << "(" << data[i].first << "," << data[i].second << "," << indexTable[data[i].first] << ")";
  }
  cout << endl;
}

// i: the index to start at when heapifying down
void hashheap::heapify(int i)
{
  int l = 2 * i + 1, r = 2 * i + 2;
  int smallest = i;
  if (l < data.size() && data[l].second < data[smallest].second)
    smallest = l;
  if (r < data.size() && data[r].second < data[smallest].second)
    smallest = r;
  if (smallest != i)
  {
    // Swap the indices
    int tmp = indexTable[data[i].first];
    indexTable[data[i].first] = indexTable[data[smallest].first];
    indexTable[data[smallest].first] = tmp;

    // Swap the data
    swap(data[i], data[smallest]);

    heapify(smallest);
  }
}

int hashheap::parent(int i)
{
  return (i - 1) / 2;
}
