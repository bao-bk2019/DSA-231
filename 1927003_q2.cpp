#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(const std::vector<int> &v) {
    int maxLength = 1; 
    int currentLength = 1; 

   
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] == v[i - 1]) {
            ++currentLength;
        } else {
            maxLength = std::max(maxLength, currentLength);
            currentLength = 1;
        }
    }

    maxLength = std::max(maxLength, currentLength);

    return maxLength;
}


int main() {
    vector<int> v = {1, 1, 2, 2, 2, 4, 4, 4, 4, 4, 4};
    int result = maxSubArray(v);
    cout << "Length of the longest subarray with the same elements: " << result << endl; 
    return 0;
}
