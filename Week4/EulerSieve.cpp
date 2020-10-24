#include<cassert>
#include<numeric>
#include<vector>

using namespace std;

void EulerSieve(int n, vector<int>& res)
{
  assert(n >= 2); 

  vector<int> nums(n - 1, 0);
  iota(nums.begin(), nums.end(), 2);

  while(!nums.empty())
  {
    int n = nums.size();
    vector<int> tmp;
    tmp.reserve(n);

    int cur = nums.front();
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
      int p = cur * nums[i];
      while(j < nums.size() && nums[j] < p)
        tmp.emplace_back(nums[j++]);
      ++j;
    }
    res.emplace_back(cur);
    nums.clear();
    copy(tmp.begin() + 1, tmp.end(), back_inserter(nums));
  }
}
