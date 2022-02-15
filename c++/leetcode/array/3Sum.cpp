#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        vector<vector<int>> result;

        if (nums.size() < 3) {
            return result;
        }

        sort(nums.begin(),nums.end());

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

                while(j<third && nums[j]+nums[third] > target){
                    third--;
                }

                if (third == j) {
                    break;
                }

                if(nums[j]+nums[third] == target){
                    result.push_back({nums[i],nums[j],nums[third]});
                }
            }
        }
        return result;
    }
};
