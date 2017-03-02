/* Remove duplicates from a vector without altering the original sequence*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
int main()
{
  std::set<int> uniqueValues;
  std::vector<int> v{9,9,8,8,7,7,6,6,5,5,4,4,3,3,2,2};
  v.erase(
    std::remove_if(v.begin(), v.end(),
      [&uniqueValues](int i)
      {
        if(uniqueValues.count(i))
          return true;
        uniqueValues.insert(i);
        return false;
      }),
    v.end());
  for(auto i : v)
    std::cout << " " << i;
  std::cout << std::endl;
}
