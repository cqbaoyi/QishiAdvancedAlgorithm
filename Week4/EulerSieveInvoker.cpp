#include<iostream>
#include<vector>

#include"EulerSieve.hpp"

using namespace std;

void printRes(const vector<int>& res)
{
  for (int i = 0; i < res.size(); ++i)
  {
    cout << res[i];
    if (i % 10 == 9 || i == res.size() - 1)
      cout << endl;
    else
      cout << "\t";
   }
 }

int main()
{
   int n = 10000;
   vector<int> res;
   EulerSieve(n, res);
 
   printRes(res);
   return 0;
}
