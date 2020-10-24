#include<cmath>
#include<iostream>
#include<numeric>
#include<vector>

#include"EulerSieve.hpp"

using namespace std;

void OneSegmentSieve(const vector<int>& nums, int start, int end, vector<int>& primes)
{
  assert(start < end);

  int m = end - start;
  vector<bool> isPrime(m, true);

  for (const auto& p: primes)
  {
    int idx = nums[start] / p;
    if (nums[start] % p > 0)
      ++idx;

    while(idx * p <= nums[end - 1])
    {
      isPrime[idx * p - nums[start]] = false;
      ++idx;
    }
  }

  for (int i = 0; i < m; ++i)
  {
    if (isPrime[i])
      primes.emplace_back(nums[start + i]);
  }
}

void SegmentedSieve(int n, vector<int>& res)
{
  assert(n >= 2);
  int delta = sqrt(n);
  int n_seg = static_cast<int>(ceil(static_cast<double>(n) / static_cast<double>(delta)));

  vector<int> nums(n - 1, 0);
  iota(nums.begin(), nums.end(), 2);
  EulerSieve(delta - 1, res);

  for (int i = 1; i < n_seg; ++i)
  {
    int start = i * delta - 2;  // nums starts from 2.
    int end = min(start + delta, n - 1);
    OneSegmentSieve(nums, start, end, res);
  }
}
