#include<initializer_list>
#include<iostream>
#include<stdexcept>
#include<vector>
#include<unordered_map>

using namespace std;

class hashheap
{
  public:
    hashheap();
    hashheap(initializer_list<pair<char, double>> l);
    bool empty();
    pair<char, double> top();
    pair<char, double> extractMin();
    void insert(pair<char, double>);
    bool isIn(char c);
    void remove(char c);
    void print();

  private:
    void heapify(int i);
    int parent(int i);

    vector<pair<char, double>> data;
    unordered_map<char, int> indexTable;
};
