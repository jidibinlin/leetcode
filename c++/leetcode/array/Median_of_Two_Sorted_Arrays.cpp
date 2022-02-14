#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> nums1 = new vector<int>();
    vector<int> nums2 = new vector<int>();

    for(int i = 1;i<10;i++){
        nums1.push_back(i);
    }
    for(int i= 1;i<10;i=i+2){
        nums2.push_back(i);
    }

    s.findMedianSortedArrays(nums1,nums2);
    return 0;
}

class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int k = nums1.size() + nums2.size();
        if(k%2 == 0){
            return min(getKthElement(nums1, nums2, k/2+1),getKthElement(nums1, nums2,k/2))/2.0;
        }else{
            return getKthElement(nums1,nums2,k/2);
        }
    }

    double getKthElement(vector<int> &nums1, vector<int> &nums2,int k){
        int index1 = 0;
        int index2 = 0;

        int m = nums1.size();
        int n = nums2.size();

        while (true){
            if (index1 == m){
                return nums2[index2+k-1];
            }
            if(index2 == n){
                return nums1[index1 +k -1];
            }
            if(k == 1){
                return min(nums1[index1],nums2[index2]);
            }

            int newIndex1 = min(index1+k/2-1,m-1);
            int newIndex2 = min(index2+k/2-1,n-1);

            if(nums1[newIndex1] >= nums2[newIndex2]){
                k -= newIndex2 - index2 +1;
                index2 = newIndex2+1;
            }else{
                k -= newIndex1 - index1 +1;
                index1 = newIndex1+1;
            }

        }
    }
};
