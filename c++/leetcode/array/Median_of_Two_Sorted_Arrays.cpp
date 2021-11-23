#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int totalLen = nums1.size() + nums2.size();

        if(totalLen%2 == 0){
            return (getKthElement(nums1, nums2, totalLen/2+1)+getKthElement(nums1, nums2,totalLen/2))/2.0;
        }else{
            return getKthElement(nums1,nums2,(totalLen+1)/2);
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

            int newIndex1 = index1+k/2-1;
            int newIndex2 = index2+k/2-1;

            if(nums1[newIndex1] <= nums2[newIndex2]){
                k -= newIndex1 - index1 +1;
                index1 = newIndex1+1;
            }else{
                k -= newIndex2 - index2 +1;
                index2 = newIndex2+1;
            }
        }
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> *nums1 = new vector<int>();
    vector<int> *nums2 = new vector<int>();
  
    nums1->push_back(1);
  
    nums2->push_back(2);
    nums2->push_back(3);
    nums2->push_back(4);
    nums2->push_back(5);
    nums2->push_back(6);

    double result = s.findMedianSortedArrays(*nums1,*nums2);
    cout << result<<endl;
}
