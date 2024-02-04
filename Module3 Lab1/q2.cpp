#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

class Solution {
public:
    using SweetnessType = int;  

    int minStepsToReachTargetSweetness(SweetnessType target, std::vector<SweetnessType>& candies) {
        std::priority_queue<SweetnessType, std::vector<SweetnessType>, std::greater<SweetnessType>> minHeap(candies.begin(), candies.end());

        int steps = 0;
        while (minHeap.top() < target) {
            SweetnessType leastSweet = minHeap.top();
            minHeap.pop();
            SweetnessType secondLeastSweet = minHeap.top();
            minHeap.pop();

            SweetnessType newSweetness = leastSweet + 2 * secondLeastSweet;
            minHeap.push(newSweetness);
            steps++;
        }

        return steps;
    }
};

int main() {
    Solution solution;
    Solution::SweetnessType target;
    std::cin >> target;

    std::cin.ignore();

    std::string input;
    std::getline(std::cin, input);
    
    std::stringstream ss(input);
    std::vector<Solution::SweetnessType> candies;
    Solution::SweetnessType sweetness;
    while (ss >> sweetness) {
        candies.push_back(sweetness);
    }

    int steps = solution.minStepsToReachTargetSweetness(target, candies);
    std::cout << steps << std::endl;  // Converted cout to std::cout

    return 0;
}
