#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        vector<vector<int>> = vector<vector<int>>()

        for (int i=0; i<nums.size(); ++i) {
            if (i>0 && nums[i]==nums[i-1]) {
                continue;
            }

            int third = nums.size()-1;
            int target = -nums[i];

            for (int j=i+1; j<nums.size(); j++) {
                if (j>i+1 && nums[j] == nums[j-1]) {
                    continue;
                }

                while(third> j && nums[j]+nums[third] > target){
                    third--;
                }

                if (third == j) {
                    continue;
                }

                if(nums[j]+nums[third] == target){
                    vector<int> tmp = vector<int>(3);
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[j]);
                    tmp.push_back(nums[third]);
                    nums.push_back(tmp);
                }

            }
        }
    }
};
