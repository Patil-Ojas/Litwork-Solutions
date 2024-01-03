#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;

int findMaxLength(vector<int>& nums) 
{
    int sum = 0, maxLen = 0;
    unordered_map<int, int> seen{{0, -1}};
    for (int i = 0; i < nums.size(); i++) 
    {
        sum += nums[i] == 1 ? 1 : -1;
        if (seen.count(sum))
            maxLen = std::max(maxLen, i - seen[sum]);
        else
            seen[sum] = i;
    }
    return maxLen;
}

int main() {
    
    string line;
    getline(cin, line);

    vector<int> value;
    istringstream iss(line);
    
    int num;
    while (iss >> num) 
    {
        value.push_back(num);
    }
    
    int result = findMaxLength(value);
    cout<<result<<endl;

    return 0;
}
                                                                                                                            
                                                                                                                            